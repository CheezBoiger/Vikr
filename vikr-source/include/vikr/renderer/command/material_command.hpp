//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_MATERIAL_COMMAND_HPP
#define __VIKR_MATERIAL_COMMAND_HPP


#include <vikr/renderer/command/render_command.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/shader/shader_program.hpp>
#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/util/vikr_log.hpp>

namespace vikr {


class Material;


class MaterialCommand : public RenderCommand {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(MaterialCommand);
  MaterialCommand(Material *material = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_MATERIAL)
    , m_material(material) { }

  vvoid Record(Commandbuffer &buffer) override {
    if (!m_material) {
      return;
    }
    ShaderUniformParams params;
    ShaderProgram *prgm = m_material->GetShaderProgram();
    //VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(glGetError()));

    if (prgm) {
      buffer.SetShaderProgram(prgm);
    }
    params.samplers = m_material->GetUniformSamplers();
    params.uniforms = m_material->GetMaterialValues();
    buffer.SetShaderUniforms(params);
    
  }

  Material *m_material;

};
}  // vikr
#endif // __VIKR_MATERIAL_COMMAND_HPP