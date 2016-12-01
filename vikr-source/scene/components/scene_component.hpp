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
};


/**
  Abstract Scene Component for the SceneObject.
*/
class SceneComponent {
public:


private:

  

  /**
    The Graphical Unique  InDentifier for the specified SceneComponent.
  */
  guid_t guid;
};
} // vikr
#endif // __VIKR_SCENE_COMPONENT_HPP