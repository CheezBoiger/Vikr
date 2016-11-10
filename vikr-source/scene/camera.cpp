//
// Copyright (c) Mario Garcia. Under the MIT License.
#include <scene/camera.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace vikr {

vreal32 Camera::ZOOM = 45.0f;
vreal32 Camera::PITCH = 0.0f;
vreal32 Camera::YAW = -90.0f;
vreal32 Camera::SENSITIVITY = 0.25f;
vreal32 Camera::ROLL = 0.0f;


Camera::Camera(glm::vec3 world_up, glm::vec3 up, glm::vec3 front, glm::vec3 pos)
  : world_up(world_up)
  , up(up)
  , front(front)
  , pos(pos)
  , zoom(Camera::ZOOM)
  , pitch(Camera::PITCH)
  , yaw(Camera::YAW)
  , roll(Camera::ROLL) 
  , sensitivity(Camera::SENSITIVITY)
{ 
  Update();
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
vvoid Camera::Look(glm::vec2 mouse_offset, vbool constrain_pitch) {
  Look(mouse_offset.x, mouse_offset.y, constrain_pitch);
}


vvoid Camera::Look(vreal32 xoffset, vreal32 yoffset, vbool constrain_pitch) {
  xoffset *= sensitivity;
  yoffset *= sensitivity;
  yaw += xoffset;
  pitch += yoffset;
  if (constrain_pitch) {
    if (pitch > 89.0f) {
      pitch = 89.0f;
    } else if (pitch < -89.0f) {
      pitch = -89.0f;  
    }
  }
}


// Camera front vector must be facing the lookAt position!
vvoid Camera::SetLookAt(glm::vec3 new_look) {
  front = glm::normalize(new_look - pos);
}


vvoid Camera::SetViewport(vint32 x, vint32 y, vint32 width, vint32 height) {
  viewport.viewport_x = x;
  viewport.viewport_y = y;
  viewport.win_width = width;
  viewport.win_height = height;
}


// Everything gets updated!
vvoid Camera::Update() {
  if (type == CamType::ORTHOGRAPHIC) {
    projection = glm::ortho(-1.5f * float(aspect), 1.5f * float(aspect), -1.5f, 1.5f, -10.0f, 10.0f);
  } else if (type == CamType::PERSPECTIVE) {
    projection = glm::perspective(fov, aspect, near_clip, far_clip);
  }
  glm::vec3 axis = glm::cross(front, up);
  glm::quat pitch_quatern = glm::angleAxis(pitch, axis);
  glm::quat yaw_quatern = glm::angleAxis(yaw, up);
  glm::quat q = glm::normalize(glm::cross(pitch_quatern, yaw_quatern));
  front = glm::rotate(q, front);
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
  view = glm::lookAt(pos, front + pos, up);
}
} // vikr