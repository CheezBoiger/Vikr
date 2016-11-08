//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_ICAMERA_HPP
#define __VIKR_ICAMERA_HPP

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <platform/vikr_time.hpp>
#include <platform/vikr_types.hpp>
#include <renderer/viewport.hpp>

namespace vikr {


enum Camtype { ORTHOGRAPHIC, PERSPECTIVE };
enum CamDirection {
  FORWARD,
  BACK,
  UP,
  DOWN,
  LEFT,
  RIGHT
};


/**
  Camera Interface used for the rendering system.
*/
class ICamera {
public:
  ICamera() { }
  virtual ~ICamera() { }

  virtual vvoid Move(CamDirection dir, vreal32 delta) = 0;
  virtual vvoid SetPos(glm::vec3 new_pos) = 0;

  virtual glm::mat4 GetView() = 0;
  virtual glm::mat4 GetProjection() = 0;

  virtual vvoid Look(glm::vec2 mouse_offset) = 0;
  virtual vvoid Look(vreal32 xoffset, vreal32 yoffset) = 0;
  virtual vvoid SetViewport(vint32 x, vint32 y, vint32 width, vint32 height) = 0;
  virtual Viewport GetViewport() = 0;
  virtual vvoid Update() = 0;
};
} // vikr
#endif // __VIKR_ICAMERA_HPP