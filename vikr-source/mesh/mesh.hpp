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
#include <string>

namespace vikr {


/**
  OpenGL Mesh object to be used for rendering.
*/
class Mesh : public IMesh {
  static const std::string kDefaultName;
  VIKR_DISALLOW_COPY_AND_ASSIGN(Mesh);
public:
  Mesh();
  Mesh(std::vector<glm::vec3> positions, 
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> uvs,
       std::vector<vuint32> indices = std::vector<vuint32>(),
       MeshDrawMode draw_mode = vikr_TRIANGLES);

  VIKR_DEFAULT_MOVE_AND_ASSIGN(Mesh);

  vvoid Create() override;
  vvoid Create(std::vector<glm::vec3> positions, 
               std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs,
               std::vector<vuint32> indices = std::vector<vuint32>(), 
               MeshDrawMode draw_mode = vikr_TRIANGLES) override;

  vvoid Create(std::vector<Vertex> vertices, MeshDrawMode draw_mode = vikr_TRIANGLES) override;

  vvoid SetMaterial(Material *material) { m_material = material; }
  vvoid SetName(std::string name) { m_name = name; }


  vuint32 GetVAO() override { return m_vao; }
  vuint32 GetVBO() override { return m_vbo; }
  vuint32 GetEBO() override { return m_ebo; }
  Material *GetMaterial() override { return m_material; }
  MeshCommand *GetMeshCommand() override { return &m_command; }

  MeshDrawMode GetMeshMode() override { return m_mode; }
  GraphicsPipeline GetRenderType() override { return m_render_type; } 

  std::vector<Vertex>& GetVertices() { return m_vertices; }

  std::string GetName() { return m_name; }

protected:
  std::string m_name;
  MeshDrawMode m_mode;
  GraphicsPipeline m_render_type;
  vuint32 m_vao;
  vuint32 m_vbo;
  vuint32 m_ebo;
  Material *m_material;
  vbool is_transparent;

  MeshCommand m_command;

  std::vector<Vertex> m_vertices;
  std::vector<vuint32> m_indices;
};
} // vikr
#endif // __VIKR_MESH_HPP