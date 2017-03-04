//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SCENE_HPP
#define __VIKR_SCENE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <memory>

namespace vikr {


class SceneNode;
class ResourceManager;


/**
  Scene graph (built as a Direct Acyclic Graph) that contains all SceneNodes within the 
  rendering scene. this is used to determine all scenes and their associated nodes for easy
  storage, along with quick rendering set up.
*/
class Scene {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Scene);
  static SceneNode *CreateSceneNode(ResourceManager *mgr);

  Scene(SceneNode *root = nullptr);

  SceneNode *GetRoot() { return m_root; }

  vvoid SetRoot(SceneNode *n_root) { m_root = n_root; }

  /**
    Update the graph data structure, starting from root.
  */
  vvoid Update();
private:
  /**
    Root SceneObject.
  */
  SceneNode *m_root = nullptr;

  VIKR_DISALLOW_COPY_AND_ASSIGN(Scene);
};
} // vikr
#endif // __VIKR_SCENE_HPP