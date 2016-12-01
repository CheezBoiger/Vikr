//
// Copyright (c) Mario Garca, Under the MIT License.
//
#include <mesh/opengl/glmesh.hpp>


namespace vikr {


GLMesh::GLMesh() 
  : Mesh(vikr_OPENGL)
{
}


GLMesh::GLMesh(std::vector<glm::vec3> positions,
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> uvs,
       std::vector<vuint32> indices,
       MeshDrawMode draw_mode)
  : Mesh(vikr_OPENGL, positions, normals, uvs, indices, draw_mode)
{
}


vvoid GLMesh::Create() {
  if(!m_vao) {
    GenVertexArrays(1, &m_vao);
    GenBuffers(1, &m_vbo);
    GenBuffers(1, &m_ebo);
  }
  std::vector<vreal32> data;
  for(vuint32 i = 0; i < m_vertices.size(); ++i) {
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
  if(!m_indices.empty()) {
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
} // vikr