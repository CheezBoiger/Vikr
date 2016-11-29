//
// Copyright (c) Mario Garcia, Under the MIT License.
//

#include <scene/scene_obj.hpp>
#include <util/vikr_assert.hpp>


namespace vikr {


SceneObject::SceneObject()
{
}


SceneObject *SceneObject::AddChild(SceneObject *obj) {
  if (obj) {
    children.push_back(obj);
  }
  return obj;
}



} // vikr