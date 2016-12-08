//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <resources/resource_manager.hpp>
#include <scene/scene_node.hpp>
#include <scene/components/scene_component.hpp>
#include <scene/components/mesh_component.hpp>
#include <scene/components/renderer_component.hpp>
#include <scene/components/transform_component.hpp>
#include <scene/components/light_component.hpp>
#include <scene/components/camera_component.hpp>


namespace vikr {


std::unordered_map<guid_t, std::shared_ptr<SceneNode> > Resources::scene_nodes;


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
} // vikr