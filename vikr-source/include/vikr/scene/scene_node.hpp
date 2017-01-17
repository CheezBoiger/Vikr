//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_NODE_HPP
#define __VIKR_SCENE_NODE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <vikr/renderer/command/render_command.hpp>
#include <vikr/renderer/command/group_command.hpp>
#include <vikr/scene/components/scene_component.hpp>
#include <unordered_map>
#include <string>


namespace vikr {


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
  VIKR_DEFAULT_MOVE_AND_ASSIGN(SceneNode);

  /**
    Scene node default constructor.
  */
  SceneNode();  

  /**
    Get the RenderCommand.
  */
  GroupCommand *GetCommand() { return &m_commandList; }

  /*
    Takes the parent of the SceneNode. nulltpr returned if no parent 
    is assigned.
  */
  SceneNode *GetParent() { return m_parent; }

  /**
    Get a specific child associated with their tag name.
    If no child is associated with the tag name, nullptr is returned. 
    BE AWARE: This performs a linear search for the child with the specified tag!
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
    BE AWARE: This performs a linear search for the child with the specified tag!
    @param
    @return
  */
  SceneNode *RemoveChild(std::string tag);

  /**
    Removes child from the SceneNode's children structure. Will return a reference to 
    removed node, otherwise nullptr is returned if no node was found.
  */
  SceneNode *RemoveChild(guid_t guid);

  /**
    Add a child to this SceneNode.
  */
  SceneNode *AddChild(SceneNode *obj);

  /**
    Sets the parent of this SceneNode for this object.
  */
  vvoid SetParent(SceneNode *parent) { m_parent = parent; }

  
  /**
    Add a component into the SceneNode.
  */
  template<typename Component>
  Component *AddComponent() {
    static_assert(!std::is_copy_assignable<Component>(), 
      "Component needs to be moveable!");
    static_assert(std::is_base_of<SceneComponent, Component>(), 
      "Component is not a SceneComponent!"); 
    std::unique_ptr<Component> component = std::make_unique<Component>();
    ComponentType type = component->GetComponentType();
    guid_t guid = component->GetGUID();
    component->SetOwner(this);
    components[type] = std::move(component);
    m_commandList.Insert(guid, components[type].get()->GetCommand());
    return static_cast<Component *>(components[type].get());
  }

  /**
    Get the component inside this SceneNode.
  */
  template<typename Component>
  Component *GetComponent(ComponentType type) {
    static_assert(std::is_base_of<SceneComponent, Component>(),
      "Component is not a SceneComponent!");
    Component *component = nullptr;
    auto it = components.find(type);
    if (it != components.end()) {
      component = 
        static_cast<Component *>(components[it->second->GetComponentType()].get());
    }
    return component;
  }


  /**
    Remove a SceneComponent from the SceneNode with the specified guid.
    Returns true if removed SceneComponent, otherwise false returned if 
    SceneComponent guid doesn't exist.
  */
  vbool RemoveComponent(ComponentType type);

  /**
    Remove a SceneComponent with the specified tag name. Returns 
    the removed SceneComponent if successful, otherwise nullptr if
    failed. BE WARNED: This performs a linear search for the Component
    to remove!
  */
  //SceneComponent *RemoveComponent(std::string tag);
  
  /**
    Read-only GUID.
  */
  guid_t GetGUID() { return guid; }

  /**
    Update the SceneNode's children.
  */
  virtual vvoid Update();

  /**
    SceneNode's tag (or name).
  */
  std::string                 Tag; /* <<---- Will need to replace! */

protected:
  /**
    The SceneNode's parent.
  */
  SceneNode *m_parent                     = nullptr;

  /**
    The SceneNode's children references.
  */
  std::unordered_map<guid_t, SceneNode *> children;

  /**
    The SceneNode's associated components.
  */
  std::map<ComponentType, std::unique_ptr<SceneComponent> > components;

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
    RenderCommand, which will be manipulated by the Components.
  */
  GroupCommand m_commandList;

  VIKR_DISALLOW_COPY_AND_ASSIGN(SceneNode);
  /**
    Our renderer has access to this mesh command. 
    It's pretty much your friendly neighborhood Renderer.
    Comes complete with Scene and SceneComponent!
  */
  friend class Renderer;
  friend class SceneComponent;
  friend class Scene;
};
} // vikr
#endif // __VIKR_SCENE_NODE_HPP