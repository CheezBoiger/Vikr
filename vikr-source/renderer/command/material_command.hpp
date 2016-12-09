//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_MATERIAL_COMMAND_HPP
#define __VIKR_MATERIAL_COMMAND_HPP


#include <renderer/command/render_command.hpp>
#include <graphics/render_context.hpp>
#include <graphics/command_buffer.hpp>
#include <shader/material.hpp>
#include <shader/shader.hpp>
#include <shader/texture.hpp>

namespace vikr {


class Material;


class MaterialCommand : public RenderCommand {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(MaterialCommand);
  MaterialCommand(Material *material = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_MATERIAL)
    , m_material(material) { }

  vvoid Record(CommandBuffer *buffer) override {   
    // About a 20 +/- 10 ns overhead.
    buffer->SetShaderUniforms([&] () {
      Shader *shader = m_material->GetShader();
      if (shader) {
        shader->Use();
      }
      std::map<std::string, MaterialValue> *variables = m_material->GetMaterialValues();
      std::map<std::string, TextureSampler> *samplers = m_material->GetUniformSamplers();
      for(auto variable : *variables) {
        std::string s = variable.first;
        switch(variable.second.type) {
          case vikr_BOOL: shader->SetValue(s, (vint32 )variable.second.m_bool); break;
          case vikr_INT: shader->SetValue(s, variable.second.m_integer); break;
          case vikr_VEC2: shader->SetValue(s, variable.second.m_vec2); break;
          case vikr_VEC3: shader->SetValue(s, variable.second.m_vec3); break;
          case vikr_VEC4: shader->SetValue(s, variable.second.m_vec4); break;
          case vikr_MAT2: shader->SetValue(s, variable.second.m_mat2); break;
          case vikr_MAT3: shader->SetValue(s, variable.second.m_mat3); break;
          case vikr_MAT4: shader->SetValue(s, variable.second.m_mat4); break;
          case vikr_DOUBLE: shader->SetValue(s, variable.second.m_double); break;
          case vikr_FLOAT: shader->SetValue(s, variable.second.m_float); break;
          default: break;
        }
      }
      for (auto sampler : *samplers) {
        sampler.second.texture->Bind(sampler.second.i);
      }
    }); 
  }


  Material *m_material;
};
}  // vikr
#endif // __VIKR_MATERIAL_COMMAND_HPP