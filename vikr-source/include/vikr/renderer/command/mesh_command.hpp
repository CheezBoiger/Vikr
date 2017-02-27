//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_COMMAND_HPP
#define __VIKR_MESH_COMMAND_HPP

#include <vikr/renderer/command/render_command.hpp>
#include <vikr/renderer/command/render_command_types.hpp>
#include <glm/mat4x4.hpp>


namespace vikr {


class Mesh;
class Material;
class RenderTarget;


/**
  MeshCommand is a Render command used to send a command to the renderer,
  telling the engine to render a Mesh object with the associated material. It uses
  the RenderTarget to determine the Post Process that must be done on the Mesh in 
  screen space.
*/
class MeshCommand : public RenderCommand {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(MeshCommand);
  MeshCommand();

  /**
    Determines if the Mesh will be transparent.
  */
  vbool IsTransparent() { return is_transparent; }
  /**
    Is the mesh invisible. 
  */
  vbool IsInvisible() { return is_invisible; }  
  /**
    Set the mesh reference to the command. 
  */
  vvoid SetMesh(Mesh *mesh) { m_mesh = mesh; }
  Mesh *GetMesh() { return m_mesh; }
  RenderTarget *GetRenderTarget() { return render_target; }
  
  vvoid SetRenderTarget(RenderTarget *target) { render_target = target; }
  vvoid SetTransparent(vbool transparent) { is_transparent = transparent; }
  vvoid SetVisibility(vbool invisible) { is_invisible = invisible; } 
  vvoid SetTransform(glm::mat4 transform) { m_transform = transform; }

  glm::mat4 GetTransform() { return m_transform; }

  Material *GetMaterial() { return m_material; }
  vvoid SetMaterial(Material *material) { m_material = material; }

  vvoid Record(Commandbuffer &buffer) override;

private:
  vvoid InitTransform(glm::mat4 model) { m_transform = model; }
  vbool is_transparent;
  vbool is_invisible;

  // Model transform matrix.
  glm::mat4 m_transform;
  // weak ref
  /*
    Perhaps consider using guids instead?
  */
  Mesh *m_mesh                    = nullptr;
  Material *m_material            = nullptr;
  RenderTarget *render_target     = nullptr;

  friend class Mesh;
  VIKR_DISALLOW_COPY_AND_ASSIGN(MeshCommand);
};
} // vikr
#endif // __VIKR_MESH_COMMAND_HPP