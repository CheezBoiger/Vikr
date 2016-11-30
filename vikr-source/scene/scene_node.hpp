//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_NODE_HPP
#define __VIKR_SCENE_NODE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>
#include <vector>
#include <string>


namespace vikr {


/**
  The scene node type of the structure.
*/
enum SceneNodeType {
  vikr_UNKNOWN,
  vikr_MESH,
  vikr_MATERIAL,
  vikr_TEXTURE,
  vikr_LINE,
  vikr_TRIANGLE
};


/**
  SceneNode (kind of like a GameObject from Unity) is designed to hold the graph
  of the scene's nodes and their children. 
*/

 /**
  TODO(Garcia): Implement this Scene node as an abstraction as well!! lulz...

  SceneNode should be considered abstract, similar to the implementation of Pixar's RenderMan,
  Adobe Illustrator, Unreal Engine's Blueprint System, and you get the point...
*/
class SceneNode {
public:
  /**
    Scene node default constructor.
  */
  SceneNode();  

  /*
    Takes the parent of the SceneObject. nulltpr returned if no parent 
    is assigned.
  */
  SceneNode *GetParent() { return m_parent; }

  /**
    Get a specific child associated with their tag name.
    If no child is associated with the tag name, nullptr is returned. 
  */
  SceneNode *GetChild(std::string tag);

  /**
    Overloaded member function to get the child with the associated guid. 
  */
  SceneNode *GetChild(guid_t guid);

  /**
    Removes child from the SceneNode's children structure. 
    This will not delete the child! It will be received to the 
    user when a child is removed! User decides what to do with the 
    removed SceneNode. nullptr is returned if child there is no 
    child to remove.
    @param
    @return
  */
  SceneNode *RemoveChild(std::string tag);

  /**
    Add a child to this SceneNode.
  */
  SceneNode *AddChild(SceneNode *obj);

  /**
    Sets the parent of this SceneNode for this object.
  */
  vvoid SetParent(SceneNode *parent) { m_parent = parent; }

  /**
    Get the children of the SceneNode in the form of a vector.
  */
  std::vector<SceneNode *> *GetChildren() { return &children; }

  /**
    Read-only GUID.
  */
  guid_t GetGUID() { return guid; }
  /**
    Update the SceneNode's children.
  */
  virtual vvoid Update() = 0;

  /**
    SceneNode's tag (or name).
  */
  std::string                 Tag; /* <<---- Will need to replace! */

protected:
  /**
    The SceneObject's parent.
  */
  SceneNode *m_parent                     = nullptr;

  /**
    The SceneObject's children.
  */
  std::vector<SceneNode *>  children;

  /**
    The associated graphical unique id of the SceneNode.
  */
  const guid_t guid;
  
  /**
    Does our SceneNode need to be updated, provided that it's contents where changed?
  */
  vbool m_isDirty                         = false;

private:
  /**
    Scene Node type.
  */
  SceneNodeType m_sceneNodeType           = vikr_UNKNOWN;

  /**
    Our renderer has access to this mesh command. 
    It's pretty much your friendly neighborhood Renderer.
  */
  friend class Renderer;
};
} // vikr
#endif // __VIKR_SCENE_NODE_HPP