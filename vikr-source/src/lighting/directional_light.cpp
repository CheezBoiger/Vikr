//
// Copyright (c) Mario Gacia, Under the MIT License.
//
#include <vikr/lighting/directional_light.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


namespace vikr {


vuint32 DirectionalLight::directionlight_count = 0;


DirectionalLight::DirectionalLight()
  : Light(vikr_DIRECTIONLIGHT
    , glm::vec3(0.0f, 0.0f, 0.0f)
    , directionlight_count
    , glm::vec3(0.2f, 0.2f, 0.2f)
    , glm::vec3(0.01f, 0.01f, 0.01f)
    , glm::vec3(1.0f, 1.0f, 1.0f))
{
  directionlight_count++;
}


vvoid DirectionalLight::Update() {
  m_lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
  m_lightView = glm::lookAt(m_position, m_direction, glm::vec3(0.0f, 1.0f, 0.0f));
  m_lightSpaceMatrix = m_lightProjection * m_lightView;
}
} // vikr