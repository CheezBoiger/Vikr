//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_MATERIAL_COMMAND_HPP
#define __VIKR_MATERIAL_COMMAND_HPP


#include <renderer/command/render_command.hpp>
#include <shader/material.hpp>


namespace vikr {


class Material;


class MaterialCommand : public RenderCommand {
public:
  MaterialCommand(Material *material = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_MATERIAL)
    , m_material(material) { }


  Material *m_material;
};
}  // vikr
#endif // __VIKR_MATERIAL_COMMAND_HPP