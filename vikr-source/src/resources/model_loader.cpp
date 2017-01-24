//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/resources/model_loader.hpp>
#include <vikr/scene/scene.hpp>

// Assimp Importers.
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vikr/scene/scene_node.hpp>
#include <vikr/scene/components/mesh_component.hpp>
#include <vikr/scene/components/renderer_component.hpp>
#include <vikr/scene/components/transform_component.hpp>
#include <vikr/renderer/renderer.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/graphics/render_device.hpp>

#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>
#include <regex>


namespace vikr {


std::vector<Texture *> ModelLoader::loaded_textures;


SceneNode *ModelLoader::ImportModel(RenderDevice *device, std::string path, std::string name) {
  Assimp::Importer importer;
  SceneNode *node = nullptr;
  const aiScene *scene = importer.ReadFile(path, 
    aiProcess_Triangulate 
    | aiProcess_ImproveCacheLocality
    | aiProcess_CalcTangentSpace
    | aiProcess_OptimizeMeshes
    | aiProcess_FlipUVs
    | aiProcess_SortByPType);
  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Model Can not be loaded!");
  } else {
    std::string dir = path.substr(0, path.find_last_of('/'));
    node = ProcessNode(device, scene->mRootNode, scene, dir, name);
  }
  return node;
}


SceneNode *ModelLoader::ProcessNode(
  RenderDevice *device, 
  aiNode *node, 
  const aiScene *scene, 
  std::string dir,
  std::string name) 
{
  SceneNode *scene_node = Scene::CreateSceneNode(device);
  //scene_node->AddComponent<TransformComponent>();
  for (vuint32 i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    Mesh *m_mesh = ProcessMesh(device, mesh, scene);
    m_mesh->SetName(name + std::to_string(i));
    Material *m_material = ParseMaterial(device, material, dir, name + std::to_string(i));
    SceneNode *child = Scene::CreateSceneNode(device);
    MeshComponent *mc = child->AddComponent<MeshComponent>();
    mc->mesh = m_mesh;
    if (m_material) {
      RendererComponent *rc = child->AddComponent<RendererComponent>();
      rc->material = m_material;
    }
    // No transform with the model?
    aiVector3D pos;
    aiQuaterniont<vreal32> rotation;
    node->mTransformation.DecomposeNoScaling(rotation, pos);
    child->Update();
    scene_node->AddChild(child);
  }
  for (vuint32 i = 0; i < node->mNumChildren; ++i) {
    scene_node->AddChild(
      ProcessNode(device, node->mChildren[i], scene, 
        dir, name + "_" + std::to_string(i)));
  }
  //scene_node->Update();
  return scene_node;
}


Mesh *ModelLoader::ProcessMesh(RenderDevice *device, aiMesh *mesh, const aiScene *scene) {
  Mesh *m_mesh = nullptr;
  std::vector<Vertex> vertices;
  std::vector<vuint32> indices;
  // resizing for better performance amortized time.
  vertices.resize(mesh->mNumVertices);
  for (vuint32 i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;
    vertex.position = 
      glm::vec3(mesh->mVertices[i].x,
        mesh->mVertices[i].y,
        mesh->mVertices[i].z);
    vertex.normal =
      glm::vec3(mesh->mNormals[i].x,
        mesh->mNormals[i].y,
        mesh->mNormals[i].z);
    if (mesh->mTextureCoords > 0 && mesh->mTextureCoords[0]) {
      vertex.uv = 
        glm::vec2(mesh->mTextureCoords[0][i].x,
          mesh->mTextureCoords[0][i].y);
    } else {
      vertex.uv = glm::vec2(0.0f);
    }
    if (mesh->mTangents > 0) {
      // Calculate tangents.
      vertex.tangent = glm::vec3(mesh->mTangents[i].x,
        mesh->mTangents[i].y,
        mesh->mTangents[i].z);
    }
    if (mesh->mBitangents > 0) {
      vertex.bitangent = glm::vec3(mesh->mBitangents[i].x,
        mesh->mBitangents[i].y,
        mesh->mBitangents[i].z);
    } else {
      vertex.bitangent = glm::vec3(0);
    }
    vertices[i] = vertex;
  }
  for (vuint32 i = 0; i < mesh->mNumFaces; ++i) {
    aiFace *face = &mesh->mFaces[i];
    for (vuint32 j = 0; j < face->mNumIndices; ++j) { 
      indices.push_back(face->mIndices[j]);
    }
  }
  // Create our mesh, the mesh is created and buffered, as well as properly stored,
  // so no need to do much.
  m_mesh = device->GetResourceManager()->CreateMesh(vertices, indices);
  m_mesh->Create(device);
  return m_mesh;
}


Material *ModelLoader::ParseMaterial(
  RenderDevice *device
  , aiMaterial *material
  , std::string dir
  , std::string name) 
{
  Material *m_material = device->GetResourceManager()->CreateMaterial(name);
  std::string texture_name;
  vbool mask = 0x0;
  if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &file);
    std::string filepath = ModelLoader::ProcessPath(&file, dir);
    Texture *texture = device->GetResourceManager()->GetTexture(filepath);
    if (!texture) { 
      texture = device->GetResourceManager()->CreateTexture(
        TextureTarget::vikr_TEXTURE_2D, 
        filepath, 
        true);
      texture->Finalize();
    }
    if (texture) {
      texture_name = "vikr_TexAlbedo";
      m_material->SetTexture("vikr_TexAlbedo", texture, 0);
      mask |= 0x1;
    }
  }
  if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_NORMALS, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = device->GetResourceManager()->GetTexture(filepath);
    if (!texture) {
      texture = device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
      texture->Finalize();
    }
    if (texture) {
      texture_name = "vikr_TexNormal";
      m_material->SetTexture("vikr_TexNormal", texture, 1);
      mask |= 0x2;
    }
  } else if (material->GetTextureCount(aiTextureType_HEIGHT) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_HEIGHT, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = device->GetResourceManager()->GetTexture(filepath);
    if (!texture) {
      texture = device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D,
        filepath,
        true);
      texture->Finalize();
    }
    if (texture) {
      m_material->SetTexture("vikr_TexNormal", texture, 1);
      mask |= 0x2;
    }
  }
  if (material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_SPECULAR, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = device->GetResourceManager()->GetTexture(filepath);
    if (!texture) { 
      texture = device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
      texture->Finalize();
    }
    if (texture) {
      m_material->SetTexture("vikr_TexSpecular", texture, 2);
      mask |= 0x4;
    }
  }
  if (material->GetTextureCount(aiTextureType_SHININESS) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_SHININESS, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = device->GetResourceManager()->GetTexture(filepath);
    if (!texture) {
      texture = device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
      texture->Finalize();
    }
    if (texture) {
      m_material->SetTexture("vikr_TexRoughness", texture, 3);
      mask |= 0x8;  
    }
  }
  if (material->GetTextureCount(aiTextureType_AMBIENT) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_AMBIENT, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = device->GetResourceManager()->GetTexture(filepath);
    if (!texture) { 
      texture = device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
      texture->Finalize();
    }
    if (texture) {
      m_material->SetTexture("vikr_TexAmbient", texture, 4);
      mask |= 0x10;
    }
  }

  m_material->SetInt("vikr_mask", mask);
  return m_material;
}


std::string ModelLoader::ProcessPath(aiString *path, std::string dir) {
  std::regex reg("\\\\");
  std::string m_path = std::string(path->C_Str());
  if (m_path.find('/') == std::string::npos) {
    m_path = dir + "/" + m_path;
  }
  m_path = std::regex_replace(m_path, reg, "/");
  return m_path;
}
} // vikr