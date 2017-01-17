//
// Copyright (c) Mario Gacia, Under the MIT License.
//
#include <vikr/lighting/directional_light.hpp>


namespace vikr {


vuint32 DirectionalLight::directionlight_count = 0;


DirectionalLight::DirectionalLight()
  : Light(vikr_DIRECTIONLIGHT
    , glm::vec3(0.0f, 0.0f, 0.0f)
    , directionlight_count
    , glm::vec3(0.8f, 0.8f, 0.8f)
    , glm::vec3(0.05f, 0.05f, 0.05f)
    , glm::vec3(1.0f, 1.0f, 1.0f))
{
  directionlight_count++;
}
} // vikr