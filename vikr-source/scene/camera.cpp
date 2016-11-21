//
// Copyright (c) Mario Garcia. Under the MIT License.
#include <scene/camera.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace vikr {

vreal32 Camera::ZOOM = 45.0f;
vreal32 Camera::PITCH = 0.0f;
vreal32 Camera::YAW = 0.0f;
vreal32 Camera::SENSITIVITY = 0.25f;
vreal32 Camera::ROLL = 0.0f;


Camera::Camera(glm::vec3 pos, glm::vec3 world_up, glm::vec3 up, glm::vec3 front)
  : world_up(world_up)
  , up(up)
  , front(front)
  , pos(pos)
  , zoom(Camera::ZOOM)
  , pitch_rate(Camera::PITCH)
  , yaw_rate(Camera::YAW)
  , roll_rate(Camera::ROLL) 
  , sensitivity(Camera::SENSITIVITY)
  , speed(1.0f)
  , type(CamType::PERSPECTIVE)
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


// Camera front vector must be facing the lookAt position!
vvoid Camera::SetLookAt(glm::vec3 new_look) {
  look_at = new_look;
}


vvoid Camera::SetViewport(vint32 x, vint32 y, vint32 width, vint32 height) {
  viewport.viewport_x = x;
  viewport.viewport_y = y;
  viewport.win_width = width;
  viewport.win_height = height;
  aspect = (vreal32 )width / (vreal32 )height;
}


// Everything gets updated!
vvoid Camera::Update() {
  front = glm::normalize(look_at - pos);
  if (type == CamType::ORTHOGRAPHIC) {
    projection = glm::ortho(-1.5f * float(aspect), 1.5f * float(aspect), -1.5f, 1.5f, -10.0f, 10.0f);
  } else if (type == CamType::PERSPECTIVE) {
    projection = glm::perspective(fov, aspect, near_clip, far_clip);
  }
  glm::vec3 axis = glm::cross(front, up);
  glm::quat pitch_quatern = glm::angleAxis(pitch_rate, axis);
  glm::quat yaw_quatern = glm::angleAxis(yaw_rate, up);
  glm::quat q = glm::normalize(glm::cross(pitch_quatern, yaw_quatern));
  front = glm::rotate(q, front);
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
  view = glm::lookAt(pos, front + pos, up); // is as simple as getting the view...
  pitch_rate = 0; yaw_rate = 0;
}
} // vikr