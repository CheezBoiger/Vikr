//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_PRIMITIVE_COMMAND_HPP
#define __VIKR_PRIMITIVE_COMMAND_HPP

#include <graphics/render_context.hpp>
#include <renderer/command/render_command.hpp>
#include <graphics/command_buffer.hpp>
#include <mesh/mesh.hpp>


namespace vikr {


class Mesh;


class PrimitiveCommand : public RenderCommand {
public:
  PrimitiveCommand(Mesh *mesh = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_PRIMITIVE)
    , m_mesh(mesh) { }


  vvoid Record(CommandBuffer *buffer) override {
    buffer->SetQueryVertexBuffer(m_mesh->GetVertexBuffer());
    buffer->SetDraw(0, m_mesh->GetVertices().size());
  }

  Mesh *m_mesh;
};
} // vikr
#endif // __VIKR_PRIMITIVE_COMMAND_HPP