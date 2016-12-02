//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TRANSFORM_COMPONENT_HPP
#define __VIKR_TRANSFORM_COMPONENT_HPP


#include <scene/components/scene_component.hpp>
#include <scene/transform.hpp>


namespace vikr {


class TransformComponent : public SceneComponent {
public:

  vvoid Update() override;


  Transform *Transform;

};
} // vikr
#endif // __VIKR_TRANSFORM_COMPONENT_HPP