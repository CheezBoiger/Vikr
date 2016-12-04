#include <scene/first_person_camera.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <util/vikr_assert.hpp>

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


vvoid FPSCamera::Look(glm::vec2 mouse_offset, vreal32 delta, vbool constrain_pitch) {
  Look(mouse_offset.x, mouse_offset.y, delta, constrain_pitch);
}


vvoid FPSCamera::Look(vreal32 xoffset, vreal32 yoffset, vreal32 delta, vbool constrain_pitch) {
  xoffset *= sensitivity * delta;
  yoffset *= sensitivity * delta;
  yaw_rate -= xoffset;
  pitch_rate += yoffset;
  VIKR_ASSERTION(yaw_rate < 1000.0f);
  if ((pitch + pitch_rate) > glm::radians(pitch_max_deg) ||
      (pitch + pitch_rate) < glm::radians(-pitch_max_deg)) {
    pitch_rate = 0;
  }
}


vvoid FPSCamera::SetLookAt(glm::vec3 look) {
  Camera::SetLookAt(look);
  glm::vec3 temp = front;
  front = glm::normalize(look_at - pos);
  vreal32 y = front.y - temp.y;
  vreal32 theta = std::asin(y / glm::length(front));
  pitch = theta;
}


vvoid FPSCamera::Update() {
  if(type == CamType::ORTHOGRAPHIC) {
    projection = glm::ortho(-1.5f * float(aspect), 1.5f * float(aspect), -1.5f, 1.5f, -10.0f, 10.0f);
  } else if(type == CamType::PERSPECTIVE) {
    projection = glm::perspective(fov, aspect, near_clip, far_clip);
  }
  glm::vec3 axis = glm::cross(front, up);
  glm::quat pitch_quat = glm::angleAxis(pitch_rate, axis);
  glm::quat yaw_quat = glm::angleAxis(yaw_rate, world_up);
  glm::quat q = glm::normalize(glm::cross(pitch_quat, yaw_quat));
  front = glm::rotate(q, front);
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
  view = glm::lookAt(pos, front + pos, up);
  pitch += pitch_rate; yaw += yaw_rate;
  yaw_rate = 0; pitch_rate = 0;
}
} // vikr