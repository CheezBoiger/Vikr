//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <scene/components/transform_component.hpp>


namespace vikr {


TransformComponent::TransformComponent()
  : SceneComponent(vikr_COMPONENT_TRANSFORM)
{
}


vvoid TransformComponent::Update() {
  cmd.m_transform = &transform;
  transform.CalculateTransform();
}
} // vikr