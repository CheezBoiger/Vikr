//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/scene/components/scene_component.hpp>
#include <initializer_list>


namespace vikr {


SceneComponent::SceneComponent(ComponentType type)
  : component_type(type)
  , guid(GUIDGenerator::Generate())
{
}
} // vikr