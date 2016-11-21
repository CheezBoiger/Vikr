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
class RenderTarget;


class MeshCommand : public RenderCommand {
public:
  MeshCommand() : RenderCommand(RenderCommandType::RENDER_MESH) { }
  MeshCommand(MeshCommand&& mes_cmd) = default;
  MeshCommand& operator=(MeshCommand&& mesh_cmd) { return *this; }
  
  vbool IsTransparent() { return is_transparent; }
  vbool IsInvisible() { return is_invisible; }  

  Mesh *GetMesh() { return m_mesh; }
  RenderTarget *GetRenderTarget() { return render_target; }
  
  vvoid SetRenderTarget(RenderTarget *target) { render_target = target; }
  vvoid SetTransparent(vbool transparent) { is_transparent = transparent; }
  vvoid SetVisibility(vbool invisible) { is_invisible = invisible; } 
  vvoid SetTransform(glm::mat4 transform) { modelview = transform; }

  glm::mat4 GetTransform() { return modelview; }

private:
  vvoid InitTransform(glm::mat4 transform) { modelview = transform; }
  vbool is_transparent;
  vbool is_invisible;

  // Model-View Transform.
  glm::mat4 modelview;
  // weak ref
  Mesh *m_mesh;
  RenderTarget *render_target;

  friend class Mesh;
  VIKR_DISALLOW_COPY_AND_ASSIGN(MeshCommand);
};
} // vikr
#endif // __VIKR_MESH_COMMAND_HPP