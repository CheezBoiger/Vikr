//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_FRAMEBUFFER_HPP
#define __VIKR_FRAMEBUFFER_HPP

#include <platform/vikr_types.hpp>
#include <glm/glm.hpp>

namespace vikr {


class FrameBuffer {
public:

private:
  vuint32 m_id;
  vuint32 m_fbo;
  
  glm::vec3 m_clearcolor;
  vint32 m_width;
  vint32 m_height;
  vbool m_depth_and_stencil;

};
} // vikr
#endif // __VIKR_FRAMEBUFFER_HPP