//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_LIGHT_COMPONENT_HPP
#define __VIKR_LIGHT_COMPONENT_HPP


#include <scene/components/scene_component.hpp>
#include <renderer/command/light_command.hpp>
#include <lighting/light.hpp>


namespace vikr {


class LightComponent : public SceneComponent {
public:

  LightComponent() 
    : SceneComponent(vikr_COMPONENT_LIGHT)
  { }

  vvoid Update() override {
    m_command.light = light;
    // updating?
  }

  RenderCommand *GetCommand() override { return &m_command; }

  Light *light;

private:
  LightCommand m_command;
};
} // vikr
#endif // __VIKR_LIGHT_COMPONENT_HPP