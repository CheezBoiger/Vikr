#include <scene/first_person_camera.hpp>


namespace vikr {


FPSCamera::FPSCamera(vreal32 pitch_deg_max,
                     glm::vec3 pos,
                     glm::vec3 world_up,
                     glm::vec3 up,
                     glm::vec3 front)
  : pitch_max_deg(pitch_deg_max)
  , pitch(0.0f)
  , Camera(pos, world_up, up, front)
{
}

} // vikr