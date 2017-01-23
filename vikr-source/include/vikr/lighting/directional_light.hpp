//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_DIRECTIONAL_LIGHT_HPP
#define __VIKR_DIRECTIONAL_LIGHT_HPP


#include <vikr/lighting/light.hpp>


namespace vikr {


/**
  Directional light mimicks light at an infinite point. 
  It is not necessarily an inifinite point where light is emitted
  from, but it helps mimick that feelings. Think of sunlight.
*/
class DirectionalLight : public Light {
  static vuint32 directionlight_count;
public:
  DirectionalLight();

  vvoid SetDirection(glm::vec3 direction) { m_direction = direction; }
  glm::vec3 GetDirection() { return m_direction; }

  /**
    Updates the light-space matrix to use for shadows.
  */
  vvoid Update() override;

protected:

  glm::vec3 m_direction;

  glm::mat4 m_lightSpaceMatrix;
};
} // vikr
#endif // __VIKR_DIRECTIONAL_LIGHT_HPP