//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_LIGHT_HPP
#define __VIKR_LIGHT_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <glm/glm.hpp>


namespace vikr {


/**
  Light Interface.
*/
class Light {
public:
  Light() { }
  virtual ~Light() { }

  vvoid SetPos(glm::vec3 color) { m_color = color; }
  vvoid SetColor(glm::vec3 position) { m_position = position; }

  glm::vec3 GetPos() { return m_position; }
  glm::vec3 GetColor() { return m_color; }  

private:
  glm::vec3 m_color;
  glm::vec3 m_position;
};
}
#endif // __VIKR_LIGHT_HPP