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
  MeshCommand();

  vvoid Execute();


private:

  // Model-View Transform.
  glm::mat4 mv;
  Material *m_material; // weak ref 
};
} // vikr
#endif // __VIKR_MESH_COMMAND_HPP