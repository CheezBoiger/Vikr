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
#include <shader/shader_uniform_params.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


class Material;


class MaterialCommand : public RenderCommand {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(MaterialCommand);
  MaterialCommand(Material *material = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_MATERIAL)
    , m_material(material) { }

  vvoid Record(Commandbuffer *buffer) override {
    ShaderUniformParams params;
    Shader *shader = m_material->GetShader();
    //VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(glGetError()));

    if (shader) {
      buffer->SetShaderProgram(shader->GetProgramId());
    }
    params.samplers = m_material->GetUniformSamplers();
    params.uniforms = m_material->GetMaterialValues();
    buffer->SetShaderUniforms(params);
    
  }

  Material *m_material;

};
}  // vikr
#endif // __VIKR_MATERIAL_COMMAND_HPP