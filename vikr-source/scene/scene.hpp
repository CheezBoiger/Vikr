//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SCENE_HPP
#define __VIKR_SCENE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>
#include <memory>

namespace vikr {


class SceneNode;
class RenderDevice;


/**
  Scene graph (built as a Direct Acyclic Graph) that contains all SceneNodes within the 
  rendering scene. this is used to determine all scenes and their associated nodes for easy
  storage, along with quick rendering set up.
*/
class Scene {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Scene);
  static SceneNode *CreateSceneNode(RenderDevice *device);

  Scene(SceneNode *root = nullptr);

  SceneNode *GetRoot() { return root; }

  vvoid SetRoot(SceneNode *n_root) { root = n_root; }

  /**
    Update the graph data structure, starting from root.
  */
  vvoid Update();
private:
  /**
    Root SceneObject.
  */
  SceneNode *root = nullptr;

  VIKR_DISALLOW_COPY_AND_ASSIGN(Scene);
};
} // vikr
#endif // __VIKR_SCENE_HPP