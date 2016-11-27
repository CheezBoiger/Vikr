//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_NODE_HPP
#define __VIKR_SCENE_NODE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/transform.hpp>


namespace vikr {


class SceneNode {
public:
  SceneNode(vuint32 id);

    

private:
  vuint32 nodeid;
  Transform transform;
};
} // vikr
#endif // __VIKR_SCENE_NODE_HPP