//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_NODE_HPP
#define __VIKR_SCENE_NODE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/mesh_command.hpp>
#include <scene/transform.hpp>
#include <scene/guid_generator.hpp>
#include <vector>
#include <string>


namespace vikr {


class Mesh;
class Material;


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
    Attach material for the associated Mesh. If no mesh is assigned, material doesn't 
    do much.
  */
  vvoid AttachMaterial(Material *material) { mesh_command.SetMaterial(material); }
  /**
    Attach mesh for the associated Material. If no Material is assigned, mesh will render
    without the material.
  */
  vvoid AttachMesh(Mesh *mesh) { mesh_command.SetMesh(mesh); }
  /**
    Current Material attached to this SceneNode.
  */
  Material *GetMaterial() { return mesh_command.GetMaterial(); }

  /**
    Current Mesh attached to this SceneNode.
  */
  Mesh *GetMesh() { return mesh_command.GetMesh(); }

  /**
    Read-only GUID.
  */
  guid_t GetGUID() { return guid; }

  /**
    SceneNode's transform.
  */
  Transform                   Transform;

  /**
    SceneNode's tag (or name).
  */
  std::string                 Tag; /* <<---- Will need to replace! */

private:
  /**
    The SceneObject's parent.
  */
  SceneNode                 *m_parent = nullptr;

  /**
    The SceneObject's children.
  */
  std::vector<SceneNode *>  children;

  /**
    The MeshCommand for the SceneNode. 
  */
  /*
    TODO(Garcia): We will need to abstract this as a reference.
  */
  MeshCommand mesh_command;

  /**
    The associated graphical unique id of the SceneNode.
  */
  const guid_t guid;

  /**
    Our renderer has access to this mesh command. 
    It's pretty much your friendly neighborhood Renderer.
  */
  friend class Renderer;
};
} // vikr
#endif // __VIKR_SCENE_NODE_HPP