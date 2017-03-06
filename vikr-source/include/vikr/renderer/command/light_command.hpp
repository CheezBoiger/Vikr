//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_LIGHT_COMMAND_HPP
#define __VIKR_LIGHT_COMMAND_HPP


#include <vikr/renderer/command/render_command.hpp>
#include <vikr/lighting/point_light.hpp>
#include <vikr/lighting/directional_light.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/shader/shader_config.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/lighting/light.hpp>

#include <map>


namespace vikr {


class LightCommand : public RenderCommand {
public:
  LightCommand()
    : RenderCommand(RenderCommandType::COMMAND_LIGHT)
  { }


  vvoid Record(Commandbuffer &buffer) override {
    buffer.BeginRecord();
    switch (light->GetLightType()) {
      case vikr_POINTLIGHT: 
      {
        PointLight *plight = static_cast<PointLight *>(light);
        std::string id = std::to_string(plight->GetLightId());
        m_material.SetVector3fv("vikr_pointLights[" + id + "].position", plight->GetPos());
        m_material.SetVector3fv("vikr_pointLights[" + id + "].ambient", plight->GetAmbient());
        m_material.SetVector3fv("vikr_pointLights[" + id + "].diffuse", plight->GetDiffuse());
        m_material.SetVector3fv("vikr_pointLights[" + id + "].specular", plight->GetSpecular());
        m_material.SetFloat("vikr_pointLights[" + id + "].constant", plight->GetConstant());
        m_material.SetFloat("vikr_pointLights[" + id + "].linear", plight->GetLinear());
        m_material.SetFloat("vikr_pointLights[" + id + "].quadratic", plight->GetQuadratic());
        m_material.SetBool("vikr_pointLights[" + id + "].enabled", plight->IsEnabled());
      }
      break;
      case vikr_DIRECTIONLIGHT:
      {
        DirectionalLight *dlight = static_cast<DirectionalLight *>(light);
        Material dir_mat;
        std::string id = std::to_string(dlight->GetLightId());
        m_material.SetVector3fv("vikr_directionalLights[" + id + "].direction", dlight->GetDirection());
        m_material.SetVector3fv("vikr_directionalLights[" + id + "].position", dlight->GetPos());
        m_material.SetVector3fv("vikr_directionalLights[" + id + "].ambient", dlight->GetAmbient());
        m_material.SetVector3fv("vikr_directionalLights[" + id + "].diffuse", dlight->GetDiffuse());
        m_material.SetVector3fv("vikr_directionalLights[" + id + "].specular", dlight->GetSpecular());
        m_material.SetBool("vikr_directionalLights[" + id + "].enabled", dlight->IsEnabled());
      }
      break;
      case vikr_SPOTLIGHT:
      {
        // nothing yet.
      }
      break;
      default:
      break;
    }
    buffer.SetMaterial(&m_material);
    buffer.EndRecord();
  }


  Light *light;  
private:
  Material m_material;
};
} // vikr
#endif // __VIKR_LIGHT_COMMAND_HPP