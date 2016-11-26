//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_FRAMEBUFFER_HPP
#define __VIKR_FRAMEBUFFER_HPP

#include <platform/vikr_types.hpp>
#include <glm/glm.hpp>

namespace vikr {


class Texture;


class FrameBuffer {
public:

  FrameBuffer();
  FrameBuffer(vuint32 width, vuint32 height);

  vvoid SetStencilDepth(vbool stencil_depth) { m_depth_and_stencil = stencil_depth; }

  virtual vvoid Generate() = 0;  
  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }
  vvoid SetClearColor(glm::vec3 color) { m_clearcolor = color; }

  glm::vec3 GetClearColor() { return m_clearcolor; }
  vuint32 GetId() { return m_id; }


protected:
  Texture *m_texture;
  vuint32 m_id;
  vuint32 m_fbo;
  
  glm::vec3 m_clearcolor;
  vuint32 m_width;
  vuint32 m_height;
  vbool m_depth_and_stencil;

};
} // vikr
#endif // __VIKR_FRAMEBUFFER_HPP