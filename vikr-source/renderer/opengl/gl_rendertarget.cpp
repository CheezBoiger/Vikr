//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/opengl/gl_rendertarget.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


GLRenderTarget::GLRenderTarget()
{
}


GLRenderTarget::GLRenderTarget(vuint32 width, vuint32 height)
  : RenderTarget(width, height)
{
}


vvoid GLRenderTarget::Generate() {
  if (!m_fbo) {
    glGenFramebuffers(1, &m_fbo);
  }

  if (!m_texture) {
    m_texture = std::make_unique<GLTexture2D>(GLTexture2D());
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
  if (m_texture) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D,
            m_texture->GetNativeId(), 0);
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "Framebuffer: Texture was not generated to be bound to!");
  }
}


vvoid GLRenderTarget::BindDepthStencil() {
  if (m_rbo) {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
  }
}


vvoid GLRenderTarget::Bind() {
  if (m_fbo) { 
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  }
}


vvoid GLRenderTarget::Unbind() {
  if (m_fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}
} // vikr