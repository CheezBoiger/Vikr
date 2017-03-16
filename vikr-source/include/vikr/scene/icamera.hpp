//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_ICAMERA_HPP
#define __VIKR_ICAMERA_HPP

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vikr/platform/vikr_time.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/viewport.hpp>

namespace vikr {


/// Get the Type of camera, which is suppose to be the projection of the camera.
enum CamType { ORTHOGRAPHIC, PERSPECTIVE };


/// Camera direction, for which is used for movement of the camera.
enum CamDirection {
  FORWARD,
  BACK,
  UP,
  DOWN,
  LEFT,
  RIGHT
};


/// Camera Interface used for the rendering system.
class ICamera {
public:
  ICamera() { }
  virtual ~ICamera() { }

  /// Move the camera using the direction and delta time (change in time).
  virtual vvoid Move(CamDirection dir, vreal32 dt) = 0;

  /// Set the instantaneous position of the camera.
  virtual vvoid SetPos(glm::vec3 new_pos) = 0;
  
  /// Set the camera to look at some point in world space.
  virtual vvoid SetLookAt(glm::vec3 new_look) = 0;

  /// Set the clipping plane of the camera view frustum.
  virtual vvoid SetClip(vreal64 near_clip_dist, vreal64 far_clip_dist) = 0;
  
  /// Set the Type of camera { PERSPECTIVE, ORTHOGRAPHIC }.
  virtual vvoid SetType(CamType new_type) = 0;

  /// Set the camera to look at a mouse offset point.
  virtual vvoid Look(glm::vec2 mouse_offset, vbool constrain_pitch = true) = 0;
  
  /// Set the camera to look at a mouse offset point.
  virtual vvoid Look(vreal32 xoffset, vreal32 yoffset, vbool constrain_pitch = true) = 0;

  /// Get the position of the camera.
  virtual glm::vec3 &GetPos() = 0;

  /// Get the view matrix of the camera.
  virtual glm::mat4 GetView() = 0;

  /// Get the projection matrix of the camera.
  virtual glm::mat4 GetProjection() = 0;

  /// Set the viewport of the camera.
  virtual vvoid SetViewport(vint32 x, vint32 y, vint32 width, vint32 height) = 0;
  
  /// Get the viewport of the camera.
  virtual Viewport& GetViewport() = 0;

  /// Update the camera status and whatnot. Includes the change in time for quaternion based cameras.
  virtual vvoid Update(vreal32 dt) = 0;
};
} // vikr
#endif // __VIKR_ICAMERA_HPP