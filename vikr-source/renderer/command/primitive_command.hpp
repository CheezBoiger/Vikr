//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_PRIMITIVE_COMMAND_HPP
#define __VIKR_PRIMITIVE_COMMAND_HPP


#include <renderer/command/render_command.hpp>


namespace vikr {


class Mesh;


class PrimitiveCommand : public RenderCommand {
public:
  PrimitiveCommand(Mesh *mesh = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_PRIMITIVE)
    , m_mesh(mesh) { }


  Mesh *m_mesh;
};
} // vikr
#endif // __VIKR_PRIMITIVE_COMMAND_HPP