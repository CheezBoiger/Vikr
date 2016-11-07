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

namespace vikr {

/**
  Camera Interface used for the rendering system.
*/
class ICamera {
public:
  ICamera() { }
  virtual ~ICamera() { }

  virtual vvoid ApplyRelativeMovement(glm::vec3 offset) = 0;
  virtual vvoid ApplyRelativeMovement(vreal32 xoffset, vreal32 yoffset, vreal32 zoffset) = 0;
  virtual vvoid OverwritePos(vreal32 x, vreal32 y, vreal32 z) = 0;
  virtual vvoid OverwritePos(glm::vec3 new_pos) = 0;
  virtual void GenerateView() = 0;
  virtual void GenerateProjection() = 0;

  virtual vvoid Update(vreal32 delta) = 0;
};
} // vikr
#endif // __VIKR_ICAMERA_HPP