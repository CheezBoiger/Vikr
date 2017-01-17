//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_SPOTLIGHT_HPP
#define __VIKR_SPOTLIGHT_HPP


#include <vikr/lighting/light.hpp>
#include <vikr/lighting/point_light.hpp>
#include <vikr/lighting/directional_light.hpp>


namespace vikr {


/**
  Think of spot light as a flashlight or (if you ever went to a theatre play) that light that
  shines down on an actor. A spot light mimicks this approach.
*/
class SpotLight : public PointLight {
public:
  SpotLight() { }
  

  vreal32 GetCutoff() { return m_cutoff; }
  vreal32 GetOuterCutoff() { return m_outer_cutoff; }

  vvoid SetCutoff(vreal32 cutoff) { m_cutoff = cutoff; }
  vvoid SetOuterCutoff(vreal32 outer_cutoff) { m_outer_cutoff = outer_cutoff; }

  vvoid SetDirection(glm::vec3 direction) { m_direction = direction; }
  glm::vec3 GetDirection() { return m_direction; }

private:
  vreal32 m_cutoff;
  vreal32 m_outer_cutoff;
  glm::vec3 m_direction;
};
} // vikr
#endif // __VIKR_SPOTLIGHT_HPP