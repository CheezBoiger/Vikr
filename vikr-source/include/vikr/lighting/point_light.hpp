//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_POINTLIGHT_HPP
#define __VIKR_POINTLIGHT_HPP


#include <vikr/lighting/light.hpp>
#include <vikr/shader/cubemap.hpp>


namespace vikr {


/**
  Point light implementation.


   Uses the Following algorithm for shaders:

      attenuation = 1.0f / (constant + linear * distance + quadratic * distance^2)
*/
class PointLight : public Light {
  /**
    Keep in mind that this id determines the index of an array of pointlights
    for your shader, it will not be mapped to an array! You must figure out whether
    or not a light is in/active, but not destroy it! You may wish to map a light source
    to a table, but this is not really required.
  */
  static vuint32 pointlight_count;
public:
  PointLight(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
             glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
             glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f),
             glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f))
    : Light(vikr_POINTLIGHT
        , position
        , pointlight_count
        , diffuse
        , ambient
        , specular) { pointlight_count++; }

  vvoid SetConstant(vreal32 constant);
  vvoid SetLinear(vreal32 linear);
  vvoid SetQuadratic(vreal32 quadratic);
  vvoid SetRange(vreal32 range) { m_range = range; }

  vreal32 GetConstant() { return m_constant; }
  vreal32 GetLinear() { return m_linear; }
  vreal32 GetQuadratic() { return m_quadratic; }
  vreal32 GetRange() { return m_range; }

  vvoid Update() override;

protected:

  vreal32 m_range         = 15.0f;
  vreal32 m_constant      = 1.0f;
  vreal32 m_linear        = 0.014f;
  vreal32 m_quadratic     = 0.007f;
};
} // vikr
#endif // __VIKR_POINTLIGHT_HPP