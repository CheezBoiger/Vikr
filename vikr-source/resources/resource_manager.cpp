//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <resources/resource_manager.hpp>
#include <scene/scene_node.hpp>
#include <scene/components/scene_component.hpp>


namespace vikr {


std::unordered_map<guid_t, std::shared_ptr<SceneNode> > Resources::scene_nodes;
std::unordered_map<guid_t, std::shared_ptr<SceneComponent> > Resources::scene_components;

std::unique_ptr<ResourceManager> ResourceManager::resource_manager = nullptr;


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
};
} // vikr