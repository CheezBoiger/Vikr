//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_LIGHT_HPP
#define __VIKR_LIGHT_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <glm/glm.hpp>


namespace vikr {


enum LightType {
  vikr_DIRECTIONLIGHT,
  vikr_POINTLIGHT,
  vikr_SPOTLIGHT
};


/**
  Light Interface.
*/
class Light {
public:
  Light() { }
  Light(glm::vec3 position, glm::vec3 color) : m_color(color), m_position(position) { }
  virtual ~Light() { }

  vvoid SetPos(glm::vec3 position) { m_position = position; }
  vvoid SetColor(glm::vec3 color) { m_color = color; }

  glm::vec3 GetPos() { return m_position; }
  glm::vec3 GetColor() { return m_color; }  

  LightType GetLightType() { return type; }

protected:
  LightType type;
  glm::vec3 m_color;
  glm::vec3 m_position;
};
}
#endif // __VIKR_LIGHT_HPP