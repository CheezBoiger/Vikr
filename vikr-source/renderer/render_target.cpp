//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#include <renderer/render_target.hpp>

namespace vikr {


RenderTarget::RenderTarget(vuint32 width, vuint32 height, vbool has_depthstencil) 
  : depthstencil(has_depthstencil)
  , m_width(width)
  , m_height(height)
  , m_texture(nullptr)
{
  Generate();
}


vvoid RenderTarget::Generate() {
  if (!m_id) {
    glGenFramebuffers(1, &m_id);
  }
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);
  

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
} // vikr