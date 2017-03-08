//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_LIGHT_COMPONENT_HPP
#define __VIKR_LIGHT_COMPONENT_HPP


#include <vikr/scene/components/scene_component.hpp>
#include <vikr/renderer/command/light_command.hpp>
#include <vikr/lighting/light.hpp>


namespace vikr {


class LightComponent : public SceneComponent {
public:

  LightComponent() 
    : SceneComponent(vikr_COMPONENT_LIGHT)
  { }

  vvoid Update() override {
    m_command.light = light;
    // updating?
    if (light) {
      m_command.light->Update();
    }
  }

  RenderCommand *GetCommand() override { return &m_command; }

  Light *light;

private:
  LightCommand m_command;
};
} // vikr
#endif // __VIKR_LIGHT_COMPONENT_HPP