//
// Copyright (c) Mario Garcia. Under the MIT License.
#include <scene/camera.hpp>


namespace vikr {

vreal32 Camera::ZOOM = 45.0f;
vreal32 Camera::PITCH = 0.0f;
vreal32 Camera::YAW = -90.0f;
vreal32 Camera::SENSITIVITY = 0.25f;


Camera::Camera(glm::vec3 world_up, glm::vec3 up, glm::vec3 front, glm::vec3 right, glm::vec3 pos)
  : world_up(world_up)
  , up(up)
  , right(right)
  , front(front)
  , pos(pos)
  , zoom(Camera::ZOOM)
  , pitch(Camera::PITCH)
  , yaw(Camera::YAW)
  , roll(Camera::ROLL) 
  , sensitivity(Camera::SENSITIVITY)
{ 
}


vvoid Camera::Move(CamDirection dir, vreal32 delta) {
  vreal32 velocity = speed * delta;
  switch (dir) {
  case CamDirection::FORWARD:
    pos += front * velocity;
    break;
  case CamDirection::BACK:
    pos -= front * velocity;
    break;
  case CamDirection::LEFT:
    pos -= right * velocity;
    break;
  case CamDirection::RIGHT:
    pos += right * velocity;
    break;
  case CamDirection::UP:
    pos += up * velocity;
    break;
  case CamDirection::DOWN:
    pos -= up * velocity;
    break;
  }
}



// This will need to be used with quaternions.
vvoid Camera::Look(glm::vec2 mouse_offset) {
  vreal32 x = mouse_offset.x * sensitivity;
  vreal32 y = mouse_offset.y * sensitivity;
  yaw +=  x;
  pitch += y;
}


vvoid Camera::Look(vreal32 xoffset, vreal32 yoffset) {
  xoffset *= sensitivity;
  yoffset *= sensitivity;
  yaw += xoffset;
  pitch += yoffset;
}


vvoid Camera::Update() {
  
}
} // vikr