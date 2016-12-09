//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <scene/scene.hpp>
#include <graphics/render_device.hpp>
#include <resources/resource_manager.hpp>


namespace vikr {


SceneNode *Scene::CreateSceneNode(RenderDevice *device) {
  return device->GetResourceManager()->CreateSceneNode();
}


Scene::Scene(SceneNode *root)
  : m_root(root)
{
}


vvoid Scene::Update() {
  // update?
}
} // vikr