//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_CAMERA_HPP
#define __VIKR_CAMERA_HPP

#include <glm/glm.hpp>
#include <platform/vikr_time.hpp>
#include <platform/vikr_types.hpp>

namespace vikr {


class Camera {
public:
  Camera(glm::vec3 world_up, glm::vec3 up, glm::vec3 front, glm::vec3 right, glm::vec3 pos) 
  : world_up(world_up)
  , up(up)
  , right(right)
  , front(front)
  , pos(pos) { }


  glm::vec3& GetUp() { return up; }
  glm::vec3& GetPos() { return pos; }
  glm::vec3& GetFront() { return front; }
  glm::vec3& WorldUp() { return world_up; }
  glm::vec3& GetRight() { return right; }
  glm::mat4 GetViewMat() { return view; }
  glm::mat4 GetProjectionMat() { return projection; }

  virtual vvoid ApplyRelativeMovement(glm::vec3 offset);
  virtual vvoid ApplyRelativeMovement(vreal32 xoffset, vreal32 yoffset, vreal32 zoffset);
  virtual vvoid OverwritePos(vreal32 x, vreal32 y, vreal32 z);
  virtual vvoid OverwritePos(glm::vec3 new_pos);  

  virtual vvoid Update(vreal32 delta) = 0;
  
protected:
  // Up vector in the world.
  glm::vec3 world_up;
  // Up vector Y of the camera.
  glm::vec3 up;
  // Current position of the camera in the world.
  glm::vec3 pos;
  // Front vector Z of the camera.
  glm::vec3 front;
  // Right vector X of the camera.
  glm::vec3 right;

  glm::mat4 projection;
  glm::mat4 view;
};
} // vikr
#endif // __VIKR_CAMERA_HPP