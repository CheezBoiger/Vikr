//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <scene/components/scene_component.hpp>


namespace vikr {


SceneComponent::SceneComponent(ComponentType type)
  : component_type(type)
  , guid(GUIDGenerator::Generate())
{
}
} // vikr