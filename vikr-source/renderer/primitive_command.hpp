//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_PRIMITIVE_COMMAND_HPP
#define __VIKR_PRIMITIVE_COMMAND_HPP


#include <renderer/render_command.hpp>
#include <mesh/imesh.hpp>


namespace vikr {


class Mesh;


class PrimitiveCommand : public RenderCommand {
public:
  PrimitiveCommand() : RenderCommand(RenderCommandType::RENDER_PRIMITIVE)  { }
  
  vvoid SetColor(glm::vec3 c) { color = c; }
  vvoid SetMesh(Mesh *mesh) { m_mesh = mesh; }
  vvoid SetLineWidth(vreal32 width) { line_width = width; }

  glm::vec3 GetColor() { return color; } 
  Mesh *GetMesh() { return m_mesh; }
  vreal32 GetLineWidth() { return line_width; }

private:
  glm::vec3 color;
  vreal32 line_width        = 1;

  Mesh *m_mesh;
};
} // vikr
#endif // __VIKR_PRIMITIVE_COMMAND_HPP