//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/opengl/gl_rendertarget.hpp>
#include <shader/glsl/gl_texture2d.hpp>

namespace vikr {


GLRenderTarget::GLRenderTarget()
{
}


GLRenderTarget::GLRenderTarget(vuint32 width, vuint32 height)
  : RenderTarget(width, height)
{
}


vvoid GLRenderTarget::Generate() {
  if (!m_id) {
    glGenFramebuffers(1, &m_id);
  }

  if (!m_texture) {
    m_texture = new GLTexture2D(m_width, m_height);
    m_texture->Create(0);
  }

  if (!m_rbo) {
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, VIKR_DEPTH24_STENCIL8, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
  }
}


vvoid GLRenderTarget::BindTexture(vuint32 index) {
  glFramebufferTexture2D(GL_FRAMEBUFFER, index, GL_TEXTURE_2D, 0, 0);
}
} // vikr