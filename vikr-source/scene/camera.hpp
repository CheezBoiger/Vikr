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
  Camera(glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f), 
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
         glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),  
         glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));

  virtual ~Camera() { }


  glm::vec3& GetUp() { return up; }
  glm::vec3& GetPos() { return pos; }
  glm::vec3& GetFront() { return front; }
  glm::vec3& WorldUp() { return world_up; }
  glm::vec3& GetRight() { return right; }
  glm::mat4 GetView() override { return view; }
  glm::mat4 GetProjection() override { return projection; }

  vreal32 GetZoom() { return zoom; }
  vreal32 GetPitch() { return pitch; }
  vreal32 GetRoll() { return roll; }
  vreal32 GetSensitivity() { return sensitivity; }
  vreal32 GetFOV() { return fov; }
  vreal32 GetAspect() { return aspect; }
  Viewport& GetViewport() override { return viewport; }

  vvoid SetZoom(vreal32 z) { zoom = z; }
  vvoid SetPitch(vreal32 p) { pitch = p; }
  vvoid SetRoll(vreal32 r) { roll = r; }
  vvoid SetSensitivity(vreal32 s) { sensitivity = s; }
  vvoid SetFOV(vreal32 f) { fov = f ;}
  vvoid SetAspect(vreal32 a) { aspect = a; }
  vvoid SetViewport(vint32 x, vint32 y, vint32 width, vint32 height) override;
  vvoid SetLookAt(glm::vec3 new_look) override;
  vvoid SetType(CamType new_type) override { type = new_type; };

  virtual vvoid Move(CamDirection dir, vreal32 delta) override;
  virtual vvoid SetPos(glm::vec3 new_pos) override { pos = new_pos; }
  virtual vvoid SetClip(vreal64 near_clip_dist, vreal64 far_clip_dist) override {
    near_clip = near_clip_dist; far_clip = far_clip_dist;
  }
  virtual vvoid Look(glm::vec2 mouse_offset, vbool constrain_pitch = true) override;
  virtual vvoid Look(vreal32 xoffset, vreal32 yoffset, vbool constrain_pitch = true) override;

  virtual vvoid Update() override;
  
protected:
  // Up vector in the world.
  glm::vec3 world_up;
  // Up vector Y of the camera.
  glm::vec3 up;
  // Current position of the camera in the world.
  glm::vec3 pos;
  // Front vector Z of the camera. or direction of which the camera is facing
  glm::vec3 front;
  // Right vector X of the camera.
  glm::vec3 right;
  // target position of which to camera to look at. We don't need this really as 
  // it is justa temp.
  // glm::vec3 look_at;

  glm::mat4 projection;
  glm::mat4 view;

  vreal32 zoom;
  vreal32 sensitivity;
  vreal32 max_pitch;
  vreal32 pitch;
  vreal32 yaw;
  vreal32 roll;
  vreal32 speed;

  vreal32 aspect;
  vreal32 fov;
  vreal32 near_clip;
  vreal32 far_clip;   

  Viewport viewport;
  CamType type;

public:
  /**
    Default variables for the camera.
   */
  static vreal32 ZOOM;
  static vreal32 PITCH;
  static vreal32 YAW;
  static vreal32 ROLL;
  static vreal32 SENSITIVITY;
};
} // vikr
#endif // __VIKR_CAMERA_HPP