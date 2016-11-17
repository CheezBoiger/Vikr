//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <mesh/mesh.hpp>
#include <shader/material.hpp>



namespace vikr {



Mesh::Mesh()
  : m_vao(0)
  , m_vbo(0)
  , m_ebo(0)
  , m_mode(vikr_TRIANGLES)
  , m_render_type(vikr_OPENGL)
{
}


Mesh::Mesh(std::vector<glm::vec3> positions,
           std::vector<glm::vec3> normals,
           std::vector<glm::vec2> uvs,
           std::vector<vuint32> indices,
           MeshDrawMode draw_mode)
  : m_vao(0)
  , m_vbo(0)
  , m_ebo(0)
  , m_vertices(positions)
  , m_normals(normals)
  , m_uvs(uvs)
  , m_mode(draw_mode)
  , m_render_type(vikr_OPENGL)
{
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
    data.push_back(m_vertices[i].x);
    data.push_back(m_vertices[i].y);
    data.push_back(m_vertices[i].z);  
  }
  for (vuint32 i = 0; i < m_normals.size(); ++i) {
    data.push_back(m_normals[i].x);
    data.push_back(m_normals[i].y);
    data.push_back(m_normals[i].z);
  }
  for (vuint32 i = 0; i < m_uvs.size(); ++i) {
    data.push_back(m_uvs[i].x);
    data.push_back(m_uvs[i].y);
  }
  BindVertexArray(m_vao);
  BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo);
  BufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(vreal32), &data[0], GL_STATIC_DRAW);
  if (!m_indices.empty()) {
    BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    BufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(vreal32), &m_indices[0], GL_STATIC_DRAW);  
  }
  vuint32 offset = 0;
  EnableVertexAttribArray(0);
  VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)0);
  offset += m_vertices.size() * sizeof(vreal32);
  if (!m_normals.empty()) {
    EnableVertexAttribArray(1);
    VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
    offset += m_normals.size() * sizeof(vreal32);
  }
  if (!m_uvs.empty()) {
    EnableVertexAttribArray(2);
    VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
  }
  BindVertexArray(0);
 
}


vvoid Mesh::Create(std::vector<glm::vec3> positions,
                   std::vector<glm::vec3> normals,
                   std::vector<glm::vec2> uvs,
                   std::vector<vuint32> indices,
                   MeshDrawMode draw_mode)
{
  if (!positions.empty()) {
    m_vertices = positions;
    m_vertices = normals;
    m_uvs = uvs;
    m_indices = indices;
    m_mode = draw_mode;
  }
  Create();
}


vvoid Mesh::Draw() {
  
}
} // vikr