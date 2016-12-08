//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_MATERIAL_COMMAND_HPP
#define __VIKR_MATERIAL_COMMAND_HPP


#include <renderer/command/render_command.hpp>
#include <graphics/render_context.hpp>
#include <shader/material.hpp>
#include <shader/shader.hpp>

namespace vikr {


class Material;


class MaterialCommand : public RenderCommand {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(MaterialCommand);
  MaterialCommand(Material *material = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_MATERIAL)
    , m_material(material) { }

  vvoid Execute(CommandBuffer *buffer) override {
    Shader *shader = m_material->GetShader();
    shader->Use();
  }


  Material *m_material;
};
}  // vikr
#endif // __VIKR_MATERIAL_COMMAND_HPP