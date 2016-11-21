//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_POINTLIGHT_HPP
#define __VIKR_POINTLIGHT_HPP


#include <lighting/light.hpp>


namespace vikr {


/**
  Point light implementation.
*/
class PointLight : public Light {
public:
  PointLight(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
             glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f))
    : Light(position, color) { type = vikr_POINTLIGHT; }

  
private:

};
} // vikr
#endif // __VIKR_POINTLIGHT_HPP