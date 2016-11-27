//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_NODE_HPP
#define __VIKR_SCENE_NODE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/transform.hpp>
#include <vector>
#include <string>


namespace vikr {


class Mesh;
class Material;


/**
  Scene Object (much like a GameObject from Unity) is designed to hold the graph
  of the scene's objects and their children.
*/
class SceneObject {
public:
  SceneObject();  

  
  SceneObject *GetParent() { return parent; }
  SceneObject *GetChild(std::string tag);
  SceneObject *RemoveChild(std::string tag);
  
  std::vector<SceneObject *> GetChildren() { return children; }
  /**
    SceneObject's transform.
  */
  Transform                   Transform;
  /**
    SceneObject's tag (or name).
  */
  std::string                 Tag;

private:
  /**
    The SceneObject's parent.
  */
  SceneObject                 *parent = nullptr;
  /**
    The SceneObject's children.
  */
  std::vector<SceneObject *>  children;
  /**
    The Mesh associated with this SceneObject.
  */
  Mesh                        *m_meshObject;
  /**
    The Material associated with this SceneObject.
  */
  Material                    *m_materialObject;    
};
} // vikr
#endif // __VIKR_SCENE_NODE_HPP