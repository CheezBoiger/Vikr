//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SCENE_HPP
#define __VIKR_SCENE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>
#include <unordered_map>


namespace vikr {


class SceneNode;


/**
  Scene graph (built as a Direct Acyclic Graph) that contains all SceneNodes within the 
  rendering scene. this is used to determine all scenes and their associated nodes for easy
  storage, along with quick rendering set up.
*/
class Scene {
public:
  Scene(SceneNode *root = nullptr);

  SceneNode *GetRoot() { return root; }

  vvoid SetRoot(SceneNode *n_root) { root = n_root; }
  /**
    Get the scene node in the map.
  */
  SceneNode *GetSceneNode(guid_t guid);
private:
  /**
    Root SceneObject.
  */
  SceneNode *root = nullptr;
  /**
    All objects referenced by the scene.
  */
  std::unordered_map<guid_t, SceneNode *> objects; 
};
} // vikr
#endif // __VIKR_SCENE_HPP