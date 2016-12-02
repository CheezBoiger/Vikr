//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <scene/scene_node.hpp>
#include <scene/components/scene_component.hpp>
#include <util/vikr_assert.hpp>
#include <algorithm>

namespace vikr {


SceneNode::SceneNode()
  : guid(GUIDGenerator::Generate()) // for now...
{
}


SceneNode *SceneNode::GetChild(std::string tag) {
  SceneNode *node = nullptr;
  /*
    NOTE: This can be easily cleaned up with an auto, for each loop.
  */
  for (std::unordered_map<guid_t, SceneNode *>::iterator it = children.begin();
       it != children.end();
       ++it)
  {
    if (it->second->Tag.compare(tag) == 0) {
      node = it->second;
      break;
    }
  }
  return node;
}


SceneNode *SceneNode::GetChild(guid_t guid) {
  SceneNode *node = nullptr;
  auto it = children.find(guid);
  if (it != children.end()) { 
    node = children[it->second->guid];
  }
  return node;
}


SceneNode *SceneNode::AddChild(SceneNode *obj) {
  SceneNode *node = nullptr;
  obj->SetParent(this);
  node = children[obj->guid];
  children[obj->guid] = node;
  return node;
}


SceneNode *SceneNode::RemoveChild(guid_t guid) {
  SceneNode *node = nullptr;
  auto it = children.find(guid);
  if (it != children.end()) {
    node = children[it->second->guid];
    node->SetParent(nullptr);
    children.erase(it->second->guid);  
  }
  return node;
}


SceneNode *SceneNode::RemoveChild(std::string tag) {
  SceneNode *node = nullptr;
  /*
    NOTE(Garcia): This can easily be cleaned up with an auto or a for each loop.
  */
  for (std::unordered_map<guid_t, SceneNode *>::iterator it = children.begin();
       it != children.end();
       ++it)
  {
    if (it->second->Tag.compare(tag) == 0) {
      node = it->second;
      node->SetParent(nullptr);
      children.erase(it->second->guid);
      break;  
    }
  }
  return node;
}


SceneComponent *SceneNode::AddComponent(SceneComponent *component) {
  SceneComponent *comp = nullptr;
  if (component) {
    component->SetOwner(this);
    comp = components[component->GetGUID()];
    components[component->GetGUID()] = component;
  }
  return comp;
}


SceneComponent *SceneNode::RemoveComponent(guid_t guid) {
  SceneComponent *component = nullptr;
  auto it = components.find(guid);
  if (it != components.end()) { 
    component = components[it->second->GetGUID()];
    component->SetOwner(nullptr);
    components.erase(it->second->GetGUID());
  }
  return component;
}


SceneComponent *SceneNode::GetComponent(guid_t guid) {
  SceneComponent *component = nullptr;
  auto it = components.find(guid);
  if (it != components.end()) { 
    component = components[it->second->GetGUID()];
  }
  return component;
}


/**
  Standard update to all chilren.
*/
vvoid SceneNode::Update() {
  for (auto it = components.begin();
       it != components.end();
       ++it)
  {
    it->second->Update();
  }
  for (auto it = children.begin();
       it != children.end();
       ++it)
  {
    it->second->Update();
  }
}
} // vikr