//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_DEBUG_COMMAND_HPP
#define __VIKR_DEBUG_COMMAND_HPP


#include <vikr/renderer/command/render_command.hpp>
#include <vikr/mesh/imesh.hpp>


namespace vikr {


class Mesh;


class DebugCommand : public RenderCommand {
public:
  DebugCommand() : RenderCommand(RenderCommandType::COMMAND_DEBUG)  { }
  
  vvoid SetColor(glm::vec3 c) { color = c; }
  vvoid SetMesh(Mesh *mesh) { m_mesh = mesh; }
  vvoid SetLineWidth(vreal32 width) { line_width = width; }

  glm::vec3 GetColor() { return color; } 
  Mesh *GetMesh() { return m_mesh; }
  vreal32 GetLineWidth() { return line_width; }

  vvoid Record(Commandbuffer *buffer) override {
  }

private:
  glm::vec3 color;
  vreal32 line_width        = 1;

  Mesh *m_mesh;
};
} // vikr
#endif // __VIKR_DEBUG_COMMAND_HPP