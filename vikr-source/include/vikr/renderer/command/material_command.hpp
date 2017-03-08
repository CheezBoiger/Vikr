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
#include <vikr/graphics/graphics_pipeline_state.hpp>
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
    buffer.BeginRecord();
    if (!m_material) {
      return;
    }
    ShaderProgram *prgm = m_material->GetShaderProgram();
    //VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(glGetError()));

    if (prgm) {
      buffer.SetShaderProgram(prgm);
    }
    buffer.ClearTextures();
    buffer.SetMaterial(m_material);

    buffer.EndRecord();
  }

  Material *m_material;

};
}  // vikr
#endif // __VIKR_MATERIAL_COMMAND_HPP