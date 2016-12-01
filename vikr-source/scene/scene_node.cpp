//
// Copyright (c) Mario Garcia, Under the MIT License.
//

#include <scene/scene_node.hpp>
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
  if (children.find(guid) != children.end()) {
    node = children[guid];
  }
  return node;
}


SceneNode *SceneNode::AddChild(SceneNode *obj) {
  if (obj) {
    children[obj->guid] = obj;
  }
  return obj;
}


SceneNode *SceneNode::RemoveChild(guid_t guid) {
  SceneNode *node = nullptr;
  if (children.find(guid) != children.end()) {
    node = children[guid];
    children.erase(guid);
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
      children.erase(it->second->guid);
      break;  
    }
  }
  return node;
}


/**
  Standard update to all chilren.
*/
vvoid SceneNode::Update() {
  for (auto it = children.begin();
       it != children.end();
       ++it)
  {
    it->second->Update();
  }
}
} // vikr