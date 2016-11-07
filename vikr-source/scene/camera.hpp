//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_CAMERA_HPP
#define __VIKR_CAMERA_HPP

#include <scene/icamera.hpp>


namespace vikr {

/**
  Abstract Camera for use.
*/
class Camera : public ICamera {
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

  vreal32 GetZoom() { return zoom; }
  vreal32 GetPitch() { return pitch; }
  vreal32 GetRoll() { return roll; }
  void SetZoom(vreal32 z) { zoom = z; }
  void SetPitch(vreal32 p) { pitch = p; }
  void SetRoll(vreal32 r) { roll = r; }

  virtual vvoid ApplyRelativeMovement(glm::vec3 offset) override;
  virtual vvoid ApplyRelativeMovement(vreal32 xoffset, vreal32 yoffset, vreal32 zoffset) override;
  virtual vvoid OverwritePos(vreal32 x, vreal32 y, vreal32 z) override;
  virtual vvoid OverwritePos(glm::vec3 new_pos) override;  
  virtual void GenerateView() override;
  virtual void GenerateProjection() override;

  virtual vvoid Update(vreal32 delta) override = 0;
  
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

  vreal32 zoom;
  vreal32 pitch;
  vreal32 yaw;
  vreal32 roll;

public:
  /**
    Default variables for the camera.
   */
  static vreal32 ZOOM;
  static vreal32 PITCH;
  static vreal32 YAW;
  static vreal32 ROLL;
};
} // vikr
#endif // __VIKR_CAMERA_HPP