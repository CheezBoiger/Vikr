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
#include <vikr/lighting/light.hpp>

#include <map>


namespace vikr {


class LightCommand : public RenderCommand {
public:
  LightCommand()
    : RenderCommand(RenderCommandType::COMMAND_LIGHT)
  { }


  vvoid Record(Commandbuffer &buffer) override {
    ShaderUniformParams params;
    switch (light->GetLightType()) {
      case vikr_POINTLIGHT: 
      {
        PointLight *plight = static_cast<PointLight *>(light);
        std::string id = std::to_string(plight->GetLightId());
        MaterialValue pos, ambient, diffuse, specular, constant, linear, quad, blinn;
        MaterialValue enabled;
        pos.type = vikr_UNIFORM_VEC3; pos.m_vec3 = plight->GetPos();
        ambient.type = vikr_UNIFORM_VEC3;     ambient.m_vec3 = plight->GetAmbient();
        specular.type = vikr_UNIFORM_VEC3;    specular.m_vec3 = plight->GetSpecular();
        diffuse.type = vikr_UNIFORM_VEC3;     diffuse.m_vec3 = plight->GetDiffuse();
        constant.type = vikr_UNIFORM_FLOAT;   constant.m_float = plight->GetConstant();
        linear.type = vikr_UNIFORM_FLOAT;     linear.m_float = plight->GetLinear();
        quad.type = vikr_UNIFORM_FLOAT;       quad.m_float = plight->GetQuadratic();
        enabled.type = vikr_UNIFORM_BOOL;     enabled.m_bool = plight->IsEnabled();
        light_params = {
          std::make_pair("vikr_pointLights[" + id + "].position", pos),
          std::make_pair("vikr_pointLights[" + id + "].ambient", ambient),
          std::make_pair("vikr_pointLights[" + id + "].diffuse", diffuse),
          std::make_pair("vikr_pointLights[" + id + "].specular", specular),
          std::make_pair("vikr_pointLights[" + id + "].constant", constant),
          std::make_pair("vikr_pointLights[" + id + "].linear", linear),
          std::make_pair("vikr_pointLights[" + id + "].quadratic", quad),
          std::make_pair("vikr_pointLights[" + id + "].enabled", enabled)
        };
      }
      break;
      case vikr_DIRECTIONLIGHT:
      {
        DirectionalLight *dlight = static_cast<DirectionalLight *>(light);
        Material dir_mat;
        std::string id = std::to_string(dlight->GetLightId());
        dir_mat.SetVector3fv("vikr_directionalLights[" + id + "].direction", dlight->GetDirection());
        dir_mat.SetVector3fv("vikr_directionalLights[" + id + "].ambient", dlight->GetAmbient());
        dir_mat.SetVector3fv("vikr_directionalLights[" + id + "].diffuse", dlight->GetDiffuse());
        dir_mat.SetVector3fv("vikr_directionalLights[" + id + "].specular", dlight->GetSpecular());
        dir_mat.SetBool("vikr_directionalLights[" + id + "].enabled", dlight->IsEnabled());
        light_params = std::move(*dir_mat.GetMaterialValues());
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
    params.uniforms = &light_params;
    buffer.SetShaderUniforms(params);
  }


  Light *light;  
private:
  std::map<std::string, MaterialValue> light_params;
};
} // vikr
#endif // __VIKR_LIGHT_COMMAND_HPP