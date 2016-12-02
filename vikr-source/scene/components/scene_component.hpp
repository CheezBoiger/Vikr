//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_COMPONENT_HPP
#define __VIKR_SCENE_COMPONENT_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>


namespace vikr {


class SceneNode;


/**
  The Component type, which helps the Renderer pushback items.
*/
enum ComponentType {
  vikr_COMPONENT_NONE,
  vikr_COMPONENT_MESH,
  vikr_COMPONENT_RENDERER,
  vikr_COMPONENT_LIGHT,
  vikr_COMPONENT_CAMERA,
  vikr_COMPONENT_TRANSFORM
};


/**
  Abstract Scene Component for the SceneObject.
*/
class SceneComponent {
public:
  SceneComponent(ComponentType type = vikr_COMPONENT_NONE);

  /**
    Update component's implementation.
  */
  virtual vvoid Update() = 0;

  guid_t GetGUID() const { return guid; }

  SceneNode *GetOwner() { return owner; }
  vvoid SetOwner(SceneNode *node) { owner = node; }

protected:
  /**
    The Component type.
  */
  ComponentType component_type;

private:
  /**
    Reference to the owner of this component.
  */
  SceneNode *owner;

  /**
    The Graphical Unique  InDentifier for the specified SceneComponent.
  */
  const guid_t guid;
};
} // vikr
#endif // __VIKR_SCENE_COMPONENT_HPP