//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_LIGHT_COMMAND_HPP
#define __VIKR_LIGHT_COMMAND_HPP


#include <renderer/command/render_command.hpp>
#include <lighting/point_light.hpp>
#include <shader/shader_uniform_params.hpp>
#include <shader/shader_config.hpp>
#include <graphics/command_buffer.hpp>
#include <lighting/light.hpp>

#include <map>


namespace vikr {


class LightCommand : public RenderCommand {
public:
  LightCommand()
    : RenderCommand(RenderCommandType::COMMAND_LIGHT)
  { }


  vvoid Record(CommandBuffer *buffer) override {
    ShaderUniformParams params { nullptr, nullptr };
    switch (light->GetLightType()) {
      case vikr_POINTLIGHT: 
      {
        PointLight *plight = static_cast<PointLight *>(light);
        MaterialValue pos, ambient, diffuse, specular, constant, linear, quad, blinn;
        pos.type = vikr_VEC3; pos.m_vec3 = plight->GetPos();
        ambient.type = vikr_VEC3;     ambient.m_vec3 = plight->GetAmbient();
        specular.type = vikr_VEC3;    specular.m_vec3 = plight->GetSpecular();
        diffuse.type = vikr_VEC3;     diffuse.m_vec3 = plight->GetDiffuse();
        constant.type = vikr_FLOAT;   constant.m_float = plight->GetConstant();
        linear.type = vikr_FLOAT;     linear.m_float = plight->GetLinear();
        quad.type = vikr_FLOAT;       quad.m_float = plight->GetQuadratic();
        blinn.type = vikr_BOOL;       blinn.m_bool = true;
        light_params = {
          std::make_pair("blinn", blinn),
          std::make_pair("light_pos", pos),
          std::make_pair("light_ambient", ambient),
          std::make_pair("light_diffuse", diffuse),
          std::make_pair("light_specular", specular),
          std::make_pair("constant", constant),
          std::make_pair("linear", linear),
          std::make_pair("quadratic", quad)
        };
        params.uniforms = &light_params;
      }
      break;
      case vikr_DIRECTIONLIGHT:
      {
        // nothing yet.
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
    buffer->SetShaderUniforms(&params);
  }


  Light *light;  
private:
  std::map<std::string, MaterialValue> light_params;
};
} // vikr
#endif // __VIKR_LIGHT_COMMAND_HPP