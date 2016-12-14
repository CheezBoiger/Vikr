//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_DIRECTIONAL_LIGHT_HPP
#define __VIKR_DIRECTIONAL_LIGHT_HPP


#include <lighting/light.hpp>


namespace vikr {


class DirectionalLight : public Light {
  static vuint32 directionlight_count;
public:
  DirectionalLight();

  vvoid SetDirection(glm::vec3 direction) { m_direction = direction; }
  glm::vec3 GetDirection() { return m_direction; }

protected:

  glm::vec3 m_direction;
};
} // vikr
#endif // __VIKR_DIRECTIONAL_LIGHT_HPP