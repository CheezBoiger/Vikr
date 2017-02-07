//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/scene/camera.hpp>
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
  , velocity(1.0f)
  , type(CamType::PERSPECTIVE)
{ 
}


vvoid Camera::Move(CamDirection dir, vreal32 delta) {
  // (distance traveled from a to b) = v * dt
  vreal32 dist = velocity * delta;
  switch (dir) {
  case CamDirection::FORWARD:
    pos += front * dist;
    break;
  case CamDirection::BACK:
    pos -= front * dist;
    break;
  case CamDirection::LEFT:
    pos -= right * dist;
    break;
  case CamDirection::RIGHT:
    pos += right * dist;
    break;
  case CamDirection::UP:
    pos += up * dist;
    break;
  case CamDirection::DOWN:
    pos -= up * dist;
    break;
  }
}


// Camera front vector must be facing the lookAt position!
vvoid Camera::SetLookAt(glm::vec3 new_look) {
  look_at = new_look;
}


vvoid Camera::SetViewport(vint32 x, vint32 y, vint32 width, vint32 height) {
  viewport.win_x = x;
  viewport.win_y = y;
  viewport.win_width = width;
  viewport.win_height = height;
  aspect = (vreal32 )width / (vreal32 )height;
}


// Everything gets updated!
vvoid Camera::Update(vreal32 dt) {
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
  // Gram-shmidt process for our angles.
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
  view = glm::lookAt(pos, front + pos, up); // is as simple as getting the view...
  pitch_rate = 0; yaw_rate = 0;
}
} // vikr