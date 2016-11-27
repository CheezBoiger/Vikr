//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SCENE_HPP
#define __VIKR_SCENE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <unordered_map>


namespace vikr {


class SceneObject;


/**
  Scene graph (built as a Direct Acyclic Graph) that contains all SceneObjects within the 
  rendering scene. this is used to determine all scenes and their associated objects for easy
  storage, along with quick rendering set up.
*/
class Scene {
public:
  Scene(SceneObject *root = nullptr);

  SceneObject *GetRoot() { return root; }

  vvoid SetRoot(SceneObject *n_root) { root = n_root; }

  SceneObject *GetSceneObject(std::string tag);
private:
  /**
    Root SceneObject.
  */
  SceneObject *root = nullptr;
  /**
    All objects referenced by the scene.
  */
  std::unordered_map<std::string, SceneObject *> objects;
};
} // vikr
#endif // __VIKR_SCENE_HPP