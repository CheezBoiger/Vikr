//
// Copyright (c) Mario Garcia, Under the MIT License.
//

#include <scene/scene_node.hpp>
#include <util/vikr_assert.hpp>


namespace vikr {


SceneNode::SceneNode()
  : guid(GUIDGenerator::Generate()) // for now...
{
}


SceneNode *SceneNode::AddChild(SceneNode *obj) {
  if (obj) {
    children.push_back(obj);
  }
  return obj;
}



} // vikr