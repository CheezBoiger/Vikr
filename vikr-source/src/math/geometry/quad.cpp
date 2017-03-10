//
// Copyright (c) Mario Garcia, Under the MIT License.
//

#include <vikr/math/geometry/quad.hpp>
#include <initializer_list>


namespace vikr {


Quad::Quad() {
  std::vector<glm::vec3> positions = std::initializer_list<glm::vec3> {
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f,  -1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, -1.0f, 0.0f)
  };

  std::vector<glm::vec3> normals = std::initializer_list<glm::vec3> {
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
  };

  std::vector<glm::vec2> uvs = std::initializer_list<glm::vec2> {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f)
  };

  m_vertices.resize(positions.size());
  for (vuint32 i = 0; i < m_vertices.size(); ++i) {
    m_vertices[i].position = positions[i];
    m_vertices[i].normal = normals[i];
    m_vertices[i].uv = uvs[i];
    m_vertices[i].color = glm::vec3();
    m_vertices[i].tangent = glm::vec3();
  }
}
} // vikr