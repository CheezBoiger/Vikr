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
  
  vvoid SetTransform(glm::mat4 t) { m_transform = t; }
  vvoid SetColor(glm::vec3 c) { color = c; }
  vvoid SetMesh(Mesh *mesh) { m_mesh = mesh; }

  glm::mat4 GetTransform() { return m_transform; }
  glm::vec3 GetColor() { return color; } 
  Mesh *GetMesh() { return m_mesh; }

private:
  glm::mat4 m_transform;
  glm::vec3 color;

  Mesh *m_mesh;
};
} // vikr
#endif // __VIKR_PRIMITIVE_COMMAND_HPP