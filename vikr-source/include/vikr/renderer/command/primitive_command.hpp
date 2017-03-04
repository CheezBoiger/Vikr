//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_PRIMITIVE_COMMAND_HPP
#define __VIKR_PRIMITIVE_COMMAND_HPP

#include <vikr/graphics/render_context.hpp>
#include <vikr/renderer/command/render_command.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


class Mesh;


class PrimitiveCommand : public RenderCommand {
public:
  PrimitiveCommand(Mesh *mesh = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_PRIMITIVE)
    , m_mesh(mesh) { }


  vvoid Record(Commandbuffer &buffer) override {
    buffer.BeginRecord();
    buffer.SetQueryVertexbuffer(m_mesh->GetVertexBuffer());
    if (m_mesh->GetVertices().indices.empty()) {
      buffer.Draw(0, m_mesh->GetVertices().size);
    } else {
      buffer.DrawIndexed(nullptr, m_mesh->GetVertices().indices.size());
    }
    buffer.EndRecord();
  }

  Mesh *m_mesh;

private:

};
} // vikr
#endif // __VIKR_PRIMITIVE_COMMAND_HPP