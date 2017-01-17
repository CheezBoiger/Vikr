//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/scene/components/renderer_component.hpp>

namespace vikr {


RendererComponent::RendererComponent()
  : SceneComponent(vikr_COMPONENT_RENDERER)
{
}


vvoid RendererComponent::Update() {
  cmd.m_material = material;
}
} // vikr