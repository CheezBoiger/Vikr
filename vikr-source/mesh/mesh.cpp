//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <mesh/mesh.hpp>
#include <shader/material.hpp>
#include <util/vikr_log.hpp>
#include <memory>

namespace vikr {


const std::string Mesh::kDefaultName = "Default_Mesh";


Mesh::Mesh(GraphicsPipeline pipeline)
  : m_vao(0)
  , m_vbo(0)
  , m_ebo(0)
  , m_mode(vikr_TRIANGLES)
  , m_render_type(pipeline)
  , m_name(kDefaultName)
{
}


Mesh::Mesh(GraphicsPipeline pipeline,
           std::vector<glm::vec3> positions,
           std::vector<glm::vec3> normals,
           std::vector<glm::vec2> uvs,
           std::vector<vuint32> indices,
           MeshDrawMode draw_mode)
  : m_vao(0)
  , m_vbo(0)
  , m_ebo(0)
  , m_mode(draw_mode)
  , m_indices(indices)
  , m_render_type(pipeline)
{
  for (vuint32 i = 0; i < positions.size(); ++i) {
    Vertex vert;
    vert.position = std::move(positions[i]);
    vert.normal = std::move(normals[i]);
    vert.uv = std::move(uvs[i]);  
    m_vertices.push_back(std::move(vert));
  }
}


vvoid Mesh::Buffer(std::vector<glm::vec3> positions,
                   std::vector<glm::vec3> normals,
                   std::vector<glm::vec2> uvs,
                   std::vector<vuint32> indices,
                   MeshDrawMode draw_mode)
{
  for (vuint32 i = 0; i < positions.size(); ++i) {
    Vertex vert;
    vert.position = std::move(positions[i]);
    if (i < normals.size()) {
      vert.normal = std::move(normals[i]);
    } else {
      vert.normal = glm::vec3();
    }
    if (i < uvs.size()) {
      vert.uv = std::move(uvs[i]);
    } else {
      vert.uv = glm::vec2();
    }
    m_vertices.push_back(std::move(vert));
  }
  m_mode = draw_mode;
}


vvoid Mesh::Buffer(std::vector<Vertex> vertices, MeshDrawMode draw_mode) {
  if (!vertices.empty()) {
    m_vertices = std::move(vertices);
  }
  m_mode = draw_mode;
}
} // vikr