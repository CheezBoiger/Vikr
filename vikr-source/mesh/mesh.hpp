//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_HPP
#define __VIKR_MESH_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/mesh_command.hpp>
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
  vvoid SetModelView(glm::mat4 mv) { modelview = mv; }
  vvoid SetMaterial(Material *material) { m_material = material; }

  glm::mat4 GetModelView() { return modelview; }


  vuint32 GetVAO() override { return m_vao; }
  vuint32 GetVBO() override { return m_vbo; }
  vuint32 GetEBO() override { return m_ebo; }
  Material *GetMaterial() override { return m_material; }
  MeshCommand *GetMeshCommand() override { return &m_command; }

  MeshDrawMode GetMeshMode() override { return m_mode; }
  GraphicsPipeline GetRenderType() override { return m_render_type; } 

  std::vector<glm::vec3>& GetPositions() { return m_vertices; }
  std::vector<glm::vec3>& GetNormals() { return m_normals; }
  std::vector<glm::vec2>& GetUVs() { return m_uvs; }

protected:
  MeshDrawMode m_mode;
  GraphicsPipeline m_render_type;
  vuint32 m_vao;
  vuint32 m_vbo;
  vuint32 m_ebo;
  Material *m_material;
  vbool is_transparent;
  glm::mat4 modelview;

  MeshCommand m_command;
  // These aren't necessary to hold on to.
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