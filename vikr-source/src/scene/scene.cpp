//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/scene/scene.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/resources/resource_manager.hpp>


namespace vikr {


SceneNode *Scene::CreateSceneNode(ResourceManager *mgr) {
  return mgr->CreateSceneNode();
}


Scene::Scene(SceneNode *root)
  : m_root(root)
{
}


vvoid Scene::Update() {
  // update?
}
} // vikr