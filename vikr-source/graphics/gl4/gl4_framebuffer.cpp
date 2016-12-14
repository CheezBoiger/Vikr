//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_framebuffer.hpp>
#include <graphics/gl4/gl4_rendertarget.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <util/vikr_log.hpp>

#include <array>


namespace vikr {


GL4Framebuffer::GL4Framebuffer()
{
}


vvoid GL4Framebuffer::Generate() {
  if (!m_fbo) {
    glGenFramebuffers(1, &m_fbo);
  } else {
    VikrLog::DisplayMessage(VIKR_WARNING, 
      "A Framebuffer GUID is already assigned to this FBO. Ignoring.");
  }
}


vint32 GL4Framebuffer::IsComplete() {
  vint32 err = 1;
  // glCheckNamedFramebufferStatus is an OpenGL 4.5 API function.
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Framebuffer is not complete!");
    VikrLog::DisplayMessage(VIKR_ERROR, "GL error: " + std::to_string(glGetError()));
    std::cin.ignore();
    err = 0;
  }
  return err;
}


vvoid GL4Framebuffer::Bind() {
  if (m_fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, 
      "No framebuffer to bind to. Be sure to generate one...");
  }
}


vvoid GL4Framebuffer::Unbind() {
  if (m_fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}


vvoid GL4Framebuffer::ClearTexture(vuint32 attachment) {
  if (m_fbo) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, 
      GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, 0, 0);
  }
}


vvoid GL4Framebuffer::BindTexture(RenderTarget *target, vuint32 attachment) {
  if (m_fbo && target && target->GetRenderType() == render_TEXTURE) {
    GL4RenderTexture *texture = static_cast<GL4RenderTexture *>(target);
    if (texture->GetTexture()->GetTargetFormat() != vikr_TEXTURE_2D &&
        texture->GetTexture()->GetTargetFormat() != vikr_TEXTURE_2D_MULTISAMPLE) {
      VikrLog::DisplayMessage(VIKR_WARNING, "RenderTarget is not of Texture2D format!");
    }
    m_colorAttachments.push_back(texture->GetTexture());
    GLTexture2D *gl = static_cast<GLTexture2D *>(texture->GetTexture());
    glFramebufferTexture2D(GL_FRAMEBUFFER,
      GL_COLOR_ATTACHMENT0 + attachment, gl->GetNativeTarget(), gl->GetNativeId(), 0);
  }
}


vvoid GL4Framebuffer::DestroyFramebuffer() {
  glDeleteFramebuffers(1, &m_fbo);
}


vvoid GL4Framebuffer::BindDepthStencilBuffer(Renderbuffer *rbo) {
  if (rbo) {
    GL4Renderbuffer *buffer = static_cast<GL4Renderbuffer *>(rbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
      GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer->GetRenderbufferId());
    m_rbo = rbo;
    m_depthStencil = true;
  }
}


vvoid GL4Framebuffer::ClearDepthStencil() {
  if (m_rbo) {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
      GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
    m_rbo = 0;
    m_depthStencil = false;
  }
}


vvoid GL4Framebuffer::Validate() {
  GLenum attachments[GL_MAX_COLOR_ATTACHMENTS];
  vuint32 count = 0;
  while (count < m_colorAttachments.size()) {
    attachments[count] = GL_COLOR_ATTACHMENT0 + count;
    count++;
  }
  glDrawBuffers(count, attachments);
}
} // vikr