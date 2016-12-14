//
// Copyright (c) Mario Garcia, Under the MIT License.
//

#include <math/shape/quad.hpp>
#include <initializer_list>


namespace vikr {


Quad::Quad() {
  positions = std::initializer_list<glm::vec3> {
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f,  -1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, -1.0f, 0.0f)
  };

  normals = std::initializer_list<glm::vec3> {
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
  };

  uvs = std::initializer_list<glm::vec2> {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f)
  };
}
} // vikr