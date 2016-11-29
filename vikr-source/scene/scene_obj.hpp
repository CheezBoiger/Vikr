//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_NODE_HPP
#define __VIKR_SCENE_NODE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/mesh_command.hpp>
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

  /*
    Takes the parent of the SceneObject. nulltpr returned if no parent 
    is assigned.
  */
  SceneObject *GetParent() { return m_parent; }
  /**
    Get a specific child associated with their tag name.
    If no child is associated with the tag name, nullptr is returned. 
  */
  SceneObject *GetChild(std::string tag);
  /**
    Removes child from the SceneObject's children structure. 
    This will not delete the child! It will be received to the 
    user when a child is removed! User decides what to do with the 
    removed SceneObject. nullptr is returned if child there is no 
    child to remove.
    @param
    @return
  */
  SceneObject *RemoveChild(std::string tag);
  /**
    Add a child to this SceneObject.
  */
  SceneObject *AddChild(SceneObject *obj);
  /**
    Sets the parent of this SceneObject for this object.
  */
  vvoid SetParent(SceneObject *parent) { m_parent = parent; }
  /**
    Get the children of the SceneObject in the form of a vector.
  */
  std::vector<SceneObject *> *GetChildren() { return &children; }
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
    Current Material attached to this SceneObject.
  */
  Material *GetMaterial() { return mesh_command.GetMaterial(); }
  /**
    Current Mesh attached to this SceneObject.
  */
  Mesh *GetMesh() { return mesh_command.GetMesh(); }
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
  SceneObject                 *m_parent = nullptr;
  /**
    The SceneObject's children.
  */
  std::vector<SceneObject *>  children;

  /**
    The MeshCommand for the SceneObject.
  */
  MeshCommand mesh_command;

  /**
    Our renderer has access to this mesh command. 
    It's pretty much your friendly neighborhood Renderer.
  */
  friend class Renderer;
};
} // vikr
#endif // __VIKR_SCENE_NODE_HPP