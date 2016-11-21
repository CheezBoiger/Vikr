//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <mesh/mesh.hpp>
#include <shader/material.hpp>
#include <util/vikr_log.hpp>
#include <memory>

namespace vikr {


const std::string Mesh::kDefaultName = "Default_Mesh";


Mesh::Mesh()
  : m_vao(0)
  , m_vbo(0)
  , m_ebo(0)
  , m_mode(vikr_TRIANGLES)
  , m_render_type(vikr_OPENGL)
  , m_material(nullptr)
  , m_name(kDefaultName)
{
  m_command.m_mesh = this;
}


Mesh::Mesh(std::vector<glm::vec3> positions,
           std::vector<glm::vec3> normals,
           std::vector<glm::vec2> uvs,
           std::vector<vuint32> indices,
           MeshDrawMode draw_mode)
  : m_vao(0)
  , m_vbo(0)
  , m_ebo(0)
  , m_mode(draw_mode)
  , m_indices(indices)
  , m_render_type(vikr_OPENGL)
  , m_material(nullptr)
{
  for (vuint32 i = 0; i < positions.size(); ++i) {
    Vertex vert;
    vert.position = std::move(positions[i]);
    vert.normal = std::move(normals[i]);
    vert.uv = std::move(uvs[i]);  
    m_vertices.push_back(std::move(vert));
  }
  m_command.m_mesh = this;
  Create();
}


vvoid Mesh::Create() {
  if (!m_vao) {
    GenVertexArrays(1, &m_vao);
    GenBuffers(1, &m_vbo);
    GenBuffers(1, &m_ebo);
  }
  std::vector<vreal32> data;
  for (vuint32 i = 0; i < m_vertices.size(); ++i) {
    data.push_back(m_vertices[i].position.x);
    data.push_back(m_vertices[i].position.y);
    data.push_back(m_vertices[i].position.z);
    data.push_back(m_vertices[i].normal.x);
    data.push_back(m_vertices[i].normal.y);
    data.push_back(m_vertices[i].normal.z);
    data.push_back(m_vertices[i].uv.x);
    data.push_back(m_vertices[i].uv.y);
  }
  BindVertexArray(m_vao);
  BindBuffer(GL_ARRAY_BUFFER, m_vbo);
  BufferData(GL_ARRAY_BUFFER, data.size() * sizeof(vreal32), &data[0], GL_STATIC_DRAW);
  if (!m_indices.empty()) {
    BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    BufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(vreal32), &m_indices[0], GL_STATIC_DRAW);  
  }
  size_t stride = 3 * sizeof(vreal32);
  stride += 3 * sizeof(vreal32);
  stride += 2 * sizeof(vreal32);
  vuint32 offset = 0;
  EnableVertexAttribArray(0);  
  VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (vvoid *)offset);
  offset += 3 * sizeof(vreal32);
  EnableVertexAttribArray(1);
  VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (vvoid *)offset);
  offset += 3 * sizeof(vreal32);
  EnableVertexAttribArray(2);
  VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (vvoid *)offset);
  offset += 2 * sizeof(vreal32);
  BindVertexArray(0);
}


vvoid Mesh::Create(std::vector<glm::vec3> positions,
                   std::vector<glm::vec3> normals,
                   std::vector<glm::vec2> uvs,
                   std::vector<vuint32> indices,
                   MeshDrawMode draw_mode)
{
  for (vuint32 i = 0; i < positions.size(); ++i) {
    Vertex vert;
    vert.position = std::move(positions[i]);
    vert.normal = std::move(normals[i]);
    vert.uv = std::move(uvs[i]);
    m_vertices.push_back(std::move(vert));
  }
  m_mode = draw_mode;
  Create();
}


vvoid Mesh::Create(std::vector<Vertex> vertices, MeshDrawMode draw_mode) {
  if (!vertices.empty()) {
    m_vertices = std::move(vertices);
  }
  m_mode = draw_mode;
  Create();
}
} // vikr