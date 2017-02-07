//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_CAMERA_HPP
#define __VIKR_CAMERA_HPP

#include <vikr/scene/icamera.hpp>


namespace vikr {



/**
  Abstract, Quaternion-based camera, represented as Euler angles as well.
*/
class Camera : public ICamera {
public:
  Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f), 
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
         glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f));

  virtual ~Camera() { }

  /**
    Get the Up (Y axis) vector of the camera.
  */
  glm::vec3& GetUp() { return up; }
  /**
    Get the current position of the camera.
  */
  glm::vec3& GetPos() override { return pos; }
  /**
    Get the front (Z axis) vector of the camera.
  */
  glm::vec3& GetFront() { return front; }
  /**
    Get the Y axis vector of the world.
  */
  glm::vec3& WorldUp() { return world_up; }
  /**
    Get the Right (X axis) vector of the camera.
  */
  glm::vec3& GetRight() { return right; }
  /**
    Get the View matrix of the camera.
  */
  glm::mat4 GetView() override { return view; }
  /**
    Get the Projection matrix of the camera. This determines perspective or 
    orthographic.
  */
  glm::mat4 GetProjection() override { return projection; }
  /**
    Get the zoom scale of the camera.
  */
  vreal32 GetZoom() { return zoom; }
  /**
    Get the Pitch rate of the camera.
  */
  vreal32 GetPitch() { return pitch_rate; }
  /**
    Get the Roll rate of the camera.
  */
  vreal32 GetRoll() { return roll_rate; }
  /**
    Get the Rotation sensitivity of the camera.
  */
  vreal32 GetSensitivity() { return sensitivity; }
  /**
    Get the Field of View for the camera.
  */
  vreal32 GetFOV() { return fov; }
  /**
    Grab our Aspect ratio for the camera.
  */
  vreal32 GetAspect() { return aspect; }
  /**
    Get the viewport of our camera.
  */
  Viewport& GetViewport() override { return viewport; }
  /**
    Get the speed of the camera.
  */
  vreal32 GetSpeed() { return velocity; }
  /**
    Set methods.
  */
  vvoid SetZoom(vreal32 z) { zoom = z; }
  vvoid SetPitch(vreal32 p) { pitch_rate = p; }
  vvoid SetRoll(vreal32 r) { roll_rate = r; }
  vvoid SetSensitivity(vreal32 s) { sensitivity = s; }
  vvoid SetFOV(vreal32 f) { fov = f; }
  /**
    Setting the Aspect will update the projection.
  */
  vvoid SetAspect(vreal32 a) { aspect = a; }
  /**
    Set the viewport for the camera.
  */
  vvoid SetViewport(vint32 x, vint32 y, vint32 width, vint32 height) override;
  /**
    Set our look at vector for the camera to focus on. Uses Vector subtraction of the lookat
    and the position of the camera to find where the camera's front vector should face.
  */
  virtual vvoid SetLookAt(glm::vec3 new_look) override;
  /**
    Set our camera type (Perspective or orthographic?)
  */
  vvoid SetType(CamType new_type) override { type = new_type; };
  /**
    Set the speed of the camera's movement.
  */
  vvoid SetSpeed(vreal32 s) { velocity = s; }
  /**
    Look around with the given input.
  */
  virtual vvoid Look(glm::vec2 mouse_offset, vbool constrain_pitch = true) override { }
  /**
    Look arround with the given input.
  */
  virtual vvoid Look(vreal32 xoffset, vreal32 yoffset, vbool constrain_pitch = true) override { }
  /**
    Tells our camera to move in the determined direction.
    @param The delta time between the last frame time and the current frame time. (dt)
  */
  virtual vvoid Move(CamDirection dir, vreal32 delta) override;
  /**
    Set the position of the camera.
  */
  virtual vvoid SetPos(glm::vec3 new_pos) override { pos = new_pos; }
  /**
    This should really just be a frustum with clip space.
  */
  virtual vvoid SetClip(vreal64 near_clip_dist, vreal64 far_clip_dist) override {
    near_clip = static_cast<vreal32>(near_clip_dist); 
    far_clip = static_cast<vreal32>(far_clip_dist);
  }
  /**
    Update the camera every frame.
  */
  virtual vvoid Update(vreal32 dt) override;
  
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
  glm::vec3 look_at;

  glm::mat4 projection;
  glm::mat4 view;

  vreal32 zoom;
  vreal32 sensitivity;
  vreal32 pitch_rate;
  vreal32 yaw_rate;
  vreal32 roll_rate;
  vreal32 velocity;

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