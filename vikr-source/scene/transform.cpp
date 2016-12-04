//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <scene/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace vikr {

const glm::vec3 Transform::Front  = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 Transform::Right  = glm::vec3(1.0f, 0.0f,  0.0f);
const glm::vec3 Transform::Up     = glm::vec3(0.0f, 1.0f,  0.0f);


/**
  Calculate the Transform matrix (or the model matrix if you are a nerd.)
*/
vvoid Transform::CalculateTransform() {
  glm::mat4 _translation;
  glm::mat4 _rotation;
  glm::mat4 _scale;
  _translation = glm::translate(_translation, Position);
  _rotation = glm::toMat4(Rotation);
  _scale = glm::scale(_scale, Scale);
  // I'd like to "transform" your model matrix, hehhh heehh...
  // I suck at this...
  m_transformMatrix = _translation * _rotation * _scale;
}
} // vikr