//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/resources/resource_manager.hpp>
#include <vikr/scene/scene_node.hpp>
#include <vikr/scene/components/scene_component.hpp>
#include <vikr/scene/components/mesh_component.hpp>
#include <vikr/scene/components/renderer_component.hpp>
#include <vikr/scene/components/transform_component.hpp>
#include <vikr/scene/components/light_component.hpp>
#include <vikr/scene/components/camera_component.hpp>


namespace vikr {


std::unordered_map<guid_t, std::unique_ptr<SceneNode> > Resources::scene_nodes;
std::map<std::string, std::shared_ptr<Material> > Resources::materials;
std::map<guid_t, std::unique_ptr<Mesh> > Resources::meshes;


ResourceManager::ResourceManager(GraphicsPipeline pipe)
  : pipeline(pipe)
{
}


/**
  Creating the scene node via the resource manager.
*/
SceneNode *ResourceManager::CreateSceneNode() {
  std::unique_ptr<SceneNode> node = std::make_unique<SceneNode>();
  Resources::scene_nodes[node->GetUID()] = std::move(node);
  return Resources::scene_nodes[node->GetUID()].get();
}


SceneNode *ResourceManager::GetSceneNode(guid_t guid) {
  SceneNode *node = nullptr;
  node = Resources::scene_nodes[guid].get();
  return node;
}


vbool ResourceManager::DestroySceneNode(guid_t guid, vbool destroy_subtree) {
  return false;
}


Mesh *ResourceManager::CreateMesh(
  std::vector<glm::vec3> &positions,
  std::vector<glm::vec3> &normals,
  std::vector<glm::vec2> &uvs,
  std::vector<vuint32> &indices,
  std::vector<glm::vec3> &tangents,
  std::vector<glm::vec3> &bitangents,
  std::vector<glm::vec3> &colors)
{
  std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
  mesh->Buffer(positions, normals, uvs, indices, tangents, bitangents, colors);
  // mesh->Create();
  Resources::meshes[mesh->GetGUID()] = std::move(mesh);
  return Resources::meshes[mesh->GetGUID()].get();
}


Mesh *ResourceManager::CreateMesh(
  std::vector<Vertex> &vertices,
  std::vector<vuint32> &indices)
{
  std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
  mesh->Buffer(vertices, indices);
  //mesh->Create();
  Resources::meshes[mesh->GetGUID()] = std::move(mesh);
  return mesh.get();
}


Mesh *ResourceManager::GetMesh(guid_t guid) {
  return Resources::meshes[guid].get();
}


vbool ResourceManager::DestroyMesh(guid_t guid) {
  vbool success = false;
  auto it = Resources::meshes.find(guid);
  if(it != Resources::meshes.end()) {
    // Cleanup the mesh vertex buffer.  
    it->second->GetVertexBuffer()->Cleanup();
    Resources::meshes.erase(it);
    success = true;
  }
  return success;
}


/**
For now.
*/
Material *ResourceManager::CreateMaterial(std::string name) {
  std::shared_ptr<Material> material = std::make_shared<Material>();
  material->SetName(name);
  Resources::materials[material->GetName()] = material;
  return material.get();
}


Material *ResourceManager::GetMaterial(std::string mat_name) {
  Material *mat = nullptr;
  auto it = Resources::materials.find(mat_name);
  if (it != Resources::materials.end()) {
    mat = it->second.get();
  }
  return mat;
}


vbool ResourceManager::DestroyMaterial(std::string mat_name) {
  vbool success = false;
  auto it = Resources::materials.find(mat_name);
  if (it != Resources::materials.end()) {
    Resources::materials.erase(it);
    success = true;
  }
  return success;
}
} // vikr