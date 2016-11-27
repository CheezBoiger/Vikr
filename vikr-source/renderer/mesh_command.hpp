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

/**
  TODO(Garcia): This must be abstracted a bit.
*/
class MeshCommand : public RenderCommand {
public:
  MeshCommand();
  // these will need to be manually defined.
  MeshCommand(MeshCommand&& mes_cmd) = default;
  MeshCommand& operator=(MeshCommand&& mesh_cmd) = default;
  
  vbool IsTransparent() { return is_transparent; }
  vbool IsInvisible() { return is_invisible; }  

  Mesh *GetMesh() { return m_mesh; }
  RenderTarget *GetRenderTarget() { return render_target; }
  
  vvoid SetRenderTarget(RenderTarget *target) { render_target = target; }
  vvoid SetTransparent(vbool transparent) { is_transparent = transparent; }
  vvoid SetVisibility(vbool invisible) { is_invisible = invisible; } 
  vvoid SetModel(glm::mat4 transform) { m_model = transform; }

  glm::mat4 GetTransform() { return m_model; }

  Material *GetMaterial() { return m_material; }
  vvoid SetMaterial(Material *material) { m_material = material; }

private:
  vvoid InitModel(glm::mat4 model) { m_model = model; }
  vbool is_transparent;
  vbool is_invisible;

  // Model matrix.
  glm::mat4 m_model;
  // weak ref
  Mesh *m_mesh;
  Material *m_material;
  RenderTarget *render_target;

  friend class Mesh;
  VIKR_DISALLOW_COPY_AND_ASSIGN(MeshCommand);
};
} // vikr
#endif // __VIKR_MESH_COMMAND_HPP