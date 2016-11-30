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
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  }

  if (!m_texture) {
    GLTexture2D texture(m_width, m_height);
    texture.SetWidth(m_width);
    texture.SetFilterMin(TextureFilterMode::vikr_TEXTURE_LINEAR);
    texture.SetFormat(TextureFormat::vikr_RGB);
    texture.SetInternalFormat(TextureFormat::vikr_RGB);
    texture.SetMipmapping(false);
    texture.Create(0);
    m_texture = std::make_unique<GLTexture2D>(std::move(texture));
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
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    m_depthstencil = true;
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


vbool GLRenderTarget::IsComplete() {
  vbool success = false;
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Frame buffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return false;
  }
  return true;
}
} // vikr