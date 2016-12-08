//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <resources/model_loader.hpp>
#include <scene/scene.hpp>

// Assimp Importers.
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <scene/scene_node.hpp>
#include <scene/components/mesh_component.hpp>
#include <scene/components/renderer_component.hpp>
#include <scene/components/transform_component.hpp>
#include <renderer/renderer.hpp>
#include <shader/material.hpp>
#include <shader/texture.hpp>
#include <mesh/mesh.hpp>
#include <graphics/render_device.hpp>

#include <util/vikr_log.hpp>
#include <util/vikr_assert.hpp>


namespace vikr {


SceneNode *ModelLoader::ImportModel(RenderDevice *device, std::string path, std::string name) {
  Assimp::Importer importer;
  SceneNode *node = nullptr;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate 
                                               | aiProcess_FlipUVs 
                                               | aiProcess_GenNormals);
  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Model Can not be loaded!");
    VIKR_ASSERTION(false);
  } else {
    std::string dir = path.substr(0, path.find_last_of('/'));
    node = ProcessNode(device, scene->mRootNode, scene, dir);
  }
  return node;
}


SceneNode *ModelLoader::ProcessNode(
  RenderDevice *device, 
  aiNode *node, 
  const aiScene *scene, 
  std::string dir) 
{
  SceneNode *scene_node = Scene::CreateSceneNode(device);
  scene_node->AddComponent<TransformComponent>();
  for (vuint32 i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    Mesh *m_mesh = ProcessMesh(device, mesh, scene);
    Material *m_material = ParseMaterial(device, material, dir);
    if (node->mNumMeshes <= 1) {
      MeshComponent *mc = scene_node->AddComponent<MeshComponent>();
      mc->mesh = m_mesh;
      if (m_material) {
        RendererComponent *rp = scene_node->AddComponent<RendererComponent>();
        rp->material = m_material;
      }
      scene_node->Update();
    } else {
      SceneNode *child = Scene::CreateSceneNode(device);
      MeshComponent *mc = scene_node->AddComponent<MeshComponent>();
      RendererComponent *rp = scene_node->AddComponent<RendererComponent>();
      mc->mesh = m_mesh;
      rp->material = m_material;
      child->Update();
      scene_node->AddChild(child);
    }
  }
  for (vuint32 i = 0; i < node->mNumChildren; ++i) {
    scene_node->AddChild(ProcessNode(device, node->mChildren[i], scene, dir));
  }
  scene_node->Update();
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
    if (mesh->mTextureCoords > 0) {
      vertex.uv = 
        glm::vec2(mesh->mTextureCoords[0][i].x,
          mesh->mTextureCoords[0][i].y);
    }
    if (mesh->mTangents > 0) {
      // Calculate tangents.
    }
    vertices.push_back(vertex);
  }
  for (vuint32 i = 0; i < mesh->mNumFaces; ++i) {
    aiFace face = mesh->mFaces[i];
    for (vuint32 j = 0; j < face.mNumIndices; ++j) { 
      indices.push_back(face.mIndices[j]);
    }
  }
  // Create our mesh, the mesh is created and buffered, as well as properly stored,
  // so no need to do much.
  m_mesh = device->GetResourceManager()->CreateMesh(vertices);
  return m_mesh;
}


Material *ModelLoader::ParseMaterial(RenderDevice *device, aiMaterial *material, std::string dir) {
  Material *m_material = device->GetResourceManager()->CreateMaterial();
  if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &file);
    std::string filepath = ModelLoader::ProcessPath(&file, dir);
    Texture *texture = 
      device->GetResourceManager()->CreateTexture(
        TextureTarget::vikr_TEXTURE_2D, 
        filepath, 
        true);
    if (texture) {
      m_material->SetTexture("vikr_TexAlbedo", texture, 3);
    }
  }
  if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_NORMALS, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = 
      device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
    if (texture) {
      m_material->SetTexture("vikr_TexNormal", texture, 4);
    }
  }
  if(material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_SPECULAR, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = 
      device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
    if (texture) {
      m_material->SetTexture("vikr_TexSpecular", texture, 5);
    }
  }
  if(material->GetTextureCount(aiTextureType_SHININESS) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_SHININESS, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = 
      device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
    if (texture) {
      m_material->SetTexture("vikr_TexRoughness", texture, 6);  
    }
  }
  if (material->GetTextureCount(aiTextureType_AMBIENT) > 0) {
    aiString file;
    material->GetTexture(aiTextureType_AMBIENT, 0, &file);
    std::string filepath = ProcessPath(&file, dir);
    Texture *texture = 
      device->GetResourceManager()->CreateTexture(
        vikr_TEXTURE_2D, 
        filepath, 
        true);
    if (texture) {
      m_material->SetTexture("vikr_TexAmbient", texture, 7);
    }
  }
  return m_material;
}


std::string ModelLoader::ProcessPath(aiString *path, std::string dir) {
  std::string m_path = std::string(path->C_Str());
  if (m_path.find('/') == std::string::npos) {
    m_path = dir + "/" + m_path;
  }
  return "cat";
}
} // vikr