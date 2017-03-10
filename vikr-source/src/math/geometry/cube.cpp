//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/math/geometry/cube.hpp>
#include <initializer_list>

namespace vikr {


// Determine the way the cube must be drawn, based on
// the culling mode. This is a counter-clockwise facing order
// cube, meaning it is front facing.
Cube::Cube() {
  std::vector<glm::vec3> positions = std::initializer_list<glm::vec3> {
    // Front
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3( 1.0f, -1.0f, 1.0f),
    glm::vec3( 1.0f,  1.0f, 1.0f),
    glm::vec3( 1.0f,  1.0f, 1.0f),
    glm::vec3(-1.0f,  1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
    // Back
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3( 1.0f,  1.0f, -1.0f),
    glm::vec3( 1.0f,  1.0f, -1.0f),
    glm::vec3( 1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    // Up
    glm::vec3( 1.0f, 1.0f,  1.0f),
    glm::vec3( 1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f,  1.0f),
    glm::vec3( 1.0f, 1.0f,  1.0f),
    // Down
    glm::vec3( 1.0f, -1.0f,  1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3( 1.0f, -1.0f, -1.0f),
    glm::vec3( 1.0f, -1.0f,  1.0f),
    // Right
    glm::vec3(1.0f, -1.0f,  1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f,  1.0f, -1.0f),
    glm::vec3(1.0f,  1.0f, -1.0f),
    glm::vec3(1.0f,  1.0f,  1.0f),
    glm::vec3(1.0f, -1.0f,  1.0f),
    // Left
    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3(-1.0f,  1.0f,  1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),
  };

  // Still need to create normals.
  std::vector<glm::vec3> normals = std::initializer_list<glm::vec3> {
    // Front 
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    // Back
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),  
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    // Up
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    // Down
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
    // Right
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    // Left
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f)
  };

  std::vector<glm::vec2> uvs = std::initializer_list<glm::vec2> {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),
  };

  m_indices = std::initializer_list<vuint32> {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17,
    18, 19, 20,
    21, 22, 23,
    24, 25, 26,
    27, 28, 29,
    30, 31, 32,
    33, 34, 35
  };

  m_vertices.resize(positions.size());
  for (vuint32 i = 0; i < positions.size(); ++i) {
    m_vertices[i].position = positions[i];
    m_vertices[i].normal = normals[i];
    m_vertices[i].uv = uvs[i];
    m_vertices[i].tangent = glm::vec3();
    m_vertices[i].color = glm::vec3();
  }
}
} // vikr