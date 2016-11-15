//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_FIRST_PERSON_CAMERA_HPP
#define __VIKR_FIRST_PERSON_CAMERA_HPP

#include <scene/camera.hpp>


namespace vikr {


/**
  First-Person Shooter style camera, for free movement. This should not be part of the 
  Renderer engine, but it is useful to have one...
*/
class FPSCamera : public Camera {
public:
  FPSCamera(vreal32 pitch_deg_max = 89.0f,
            glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 world_up = glm::vec3 (0.0f, 1.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
            glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f));

  vvoid Look(glm::vec2 mouse_offset, vreal32 delta,  vbool constain_pitch = true) override;
  vvoid Look(vreal32 xoffset, vreal32 yoffset, vreal32 delta, vbool constrain_pitch = true) override;
  vvoid Update() override;
  
private:
  vreal32 pitch_max_deg;
  vreal32 yaw_max_deg;
  vreal32 pitch;
};
} // vikr 
#endif // __VIKR_FIRST_PERSON_CAMERA_HPP