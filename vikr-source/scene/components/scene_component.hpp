//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCENE_COMPONENT_HPP
#define __VIKR_SCENE_COMPONENT_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>


namespace vikr {


/**
  The Component type, which helps the Renderer pushback items.
*/
enum ComponentType {
  vikr_COMPONENT_NONE,
  vikr_COMPONENT_MESH,
  vikr_COMPONENT_RENDERER 
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

protected:
  /**
    The Component type.
  */
  ComponentType component_type;

private:


  /**
    The Graphical Unique  InDentifier for the specified SceneComponent.
  */
  guid_t guid;
};
} // vikr
#endif // __VIKR_SCENE_COMPONENT_HPP