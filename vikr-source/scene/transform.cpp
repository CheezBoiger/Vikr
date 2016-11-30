//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <scene/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace vikr {


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