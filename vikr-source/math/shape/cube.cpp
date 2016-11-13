#include <math/shape/cube.hpp>
#include <initializer_list>

namespace vikr {


// Determine the way the cube must be drawn, based on
// the culling mode. This is a counter-clockwise facing order
// cube, meaning it is front facing.
Cube::Cube() {
  m_vertices = std::initializer_list<glm::vec3> {
    // Front
    glm::vec3(-0.5f, -0.5f, 0.5f),
    glm::vec3( 0.5f, -0.5f, 0.5f),
    glm::vec3( 0.5f,  0.5f, 0.5f),
    glm::vec3( 0.5f,  0.5f, 0.5f),
    glm::vec3(-0.5f,  0.5f, 0.5f),
    glm::vec3(-0.5f, -0.5f, 0.5f),
    // Back
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    // Up
    glm::vec3( 0.5f, 0.5f,  0.5f),
    glm::vec3( 0.5f, 0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f,  0.5f),
    glm::vec3( 0.5f, 0.5f,  0.5f),
    // Down
    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f,  0.5f),
    // Right
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    // Left
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
  };

  // Still need to create normals.
  m_normals = std::initializer_list<glm::vec3> { };
}
} // vikr