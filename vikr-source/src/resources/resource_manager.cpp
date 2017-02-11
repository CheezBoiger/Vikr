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


std::unordered_map<guid_t, std::shared_ptr<SceneNode> > Resources::scene_nodes;
std::map<std::string, std::shared_ptr<Material> > Resources::materials;


ResourceManager::ResourceManager(GraphicsPipeline pipe)
  : pipeline(pipe)
{
}


/**
  Creating the scene node via the resource manager.
*/
SceneNode *ResourceManager::CreateSceneNode() {
  std::shared_ptr<SceneNode> node = std::make_shared<SceneNode>();
  Resources::scene_nodes[node->GetGUID()] = node;
  return node.get();
}


SceneNode *ResourceManager::GetSceneNode(guid_t guid) {
  SceneNode *node = nullptr;
  node = Resources::scene_nodes[guid].get();
  return node;
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