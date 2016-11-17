//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_COMMAND_HPP
#define __VIKR_MESH_COMMAND_HPP

#include <renderer/render_command.hpp>
#include <renderer/render_command_types.hpp>
#include <glm/mat4x4.hpp>


namespace vikr {


class Mesh;

class Material;

class MeshCommand : public RenderCommand {
public:
  MeshCommand() : RenderCommand(RenderCommandType::RENDER_MESH) { }
  MeshCommand(MeshCommand&& mes_cmd) = default;
  vvoid Execute() { }
  MeshCommand& operator=(MeshCommand&& mesh_cmd) { return *this; }
  
private:
  vbool is_transparent;
  vbool is_invisible;

  // Model-View Transform.
  glm::mat4 model;
  glm::mat4 view;
  Material *m_material; // weak ref 
  Mesh *m_mesh; // weak ref;

  VIKR_DISALLOW_COPY_AND_ASSIGN(MeshCommand);
};
} // vikr
#endif // __VIKR_MESH_COMMAND_HPP