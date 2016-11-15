//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_HPP
#define __VIKR_MESH_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/mesh_command.hpp>
#include <renderer/cullmode.hpp>
#include <glm/vec3.hpp>
#include <mesh/imesh.hpp>
#include <vector>

namespace vikr {


class ProgramState;
class Material;





/**
  OpenGL Mesh object to be used for rendering.
*/
class Mesh : public IMesh {
public:
  Mesh();
  Mesh(ProgramState *program);
  Mesh(std::vector<glm::vec3> positions, 
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> uvs,
       std::vector<vuint32> indices,
       MeshDrawMode draw_mode = vikr_TRIANGLES);

  vvoid Create() override;
  vvoid Create(std::vector<glm::vec3> positions, 
               std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs,
               std::vector<vuint32> indices, 
               MeshDrawMode draw_mode = vikr_TRIANGLES) override;

  vvoid Draw() override;

  vvoid SetProgramState(ProgramState *state) override { m_program = state; }
  vvoid SetMaterial(Material *material) { m_material = material; }
  ProgramState *GetProgramState() const override { return m_program; }

  vuint32 GetVAO() { return m_vao; }
  vuint32 GetVBO() { return m_vbo; }
  vuint32 GetEBO() { return m_ebo; }
  Material *GetMaterial() { return m_material; }

  MeshDrawMode GetMeshMode() override { return m_mode; }
  GraphicsPipeline GetRenderType() override { return m_render_type; } 
protected:
  MeshDrawMode m_mode;
  CullMode m_cull;
  CullFace m_face;
  GraphicsPipeline m_render_type;
  vuint32 m_vao;
  vuint32 m_vbo;
  vuint32 m_ebo;
  Material *m_material;
  ProgramState *m_program;
  vbool is_transparent;
  glm::mat4 modelview;

  MeshCommand m_command;

  std::vector<glm::vec3> m_vertices;
  std::vector<glm::vec3> m_normals;
  std::vector<vuint32> m_indices;
  std::vector<glm::vec2> m_uvs;
  // For lighting...
  std::vector<glm::vec3> m_tangents;
  std::vector<glm::vec3> m_bitangents;
};
} // vikr
#endif // __VIKR_MESH_HPP