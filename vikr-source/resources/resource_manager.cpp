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
std::unordered_map<guid_t, std::shared_ptr<SceneComponent> > Resources::scene_components;

ResourceManager *ResourceManager::resource_manager = nullptr;


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


SceneComponent *ResourceManager::CreateComponent(ComponentType type) {
  std::shared_ptr<SceneComponent> ptr = nullptr;
  switch (type) {
    case vikr_COMPONENT_MESH: ptr = std::make_shared<MeshComponent>(); break;
    case vikr_COMPONENT_RENDERER: ptr = std::make_shared<RendererComponent>(); break;
    case vikr_COMPONENT_TRANSFORM: ptr = std::make_shared<TransformComponent>(); break;
    case vikr_COMPONENT_CAMERA: break;
    case vikr_COMPONENT_LIGHT: break;
    default: break;
  }
  if (ptr) {
    Resources::scene_components[ptr->GetGUID()] = ptr;
  }
  return ptr.get();
}


SceneNode *ResourceManager::GetSceneNode(guid_t guid) {
  SceneNode *node = nullptr;
  node = Resources::scene_nodes[guid].get();
  return node;
}


SceneComponent *ResourceManager::GetSceneComponent(guid_t guid) {
  SceneComponent *component = nullptr;
  component = Resources::scene_components[guid].get();
  return component;
}
} // vikr