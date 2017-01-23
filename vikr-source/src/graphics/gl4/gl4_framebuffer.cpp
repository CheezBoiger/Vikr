//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>
#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/shader/glsl/gl_texture2d.hpp>
#include <vikr/util/vikr_log.hpp>

#include <array>


namespace vikr {


vuint32 GL4Framebuffer::GetFramebufferMode(BufferMode mode) {
  switch (mode) {
    case BufferMode::BUFFER_BACK: return GL_BACK;
    case BufferMode::BUFFER_BACK_LEFT: return GL_BACK_LEFT;
    case BufferMode::BUFFER_BACK_RIGHT: return GL_BACK_RIGHT;
    case BufferMode::BUFFER_FRONT: return GL_FRONT;
    case BufferMode::BUFFER_FRONT_LEFT: return GL_FRONT_LEFT;
    case BufferMode::BUFFER_FRONT_RIGHT: return GL_FRONT_RIGHT;
    case BufferMode::BUFFER_LEFT: return GL_LEFT;
    case BufferMode::BUFFER_RIGHT: return GL_RIGHT;
    case BufferMode::BUFFER_NONE: 
    default: return GL_NONE;
  }
}


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
    if (m_colorAttachments.find(attachment) != m_colorAttachments.end()) {
      m_colorAttachments.erase(attachment);  
    }
  }
}


vvoid GL4Framebuffer::BindTexture(RenderTarget *target, vuint32 attachment) {
  if (m_fbo && target && target->GetRenderType() == render_TEXTURE) {
    GL4RenderTexture *texture = static_cast<GL4RenderTexture *>(target);
    if (texture->GetTexture()->GetTargetFormat() != vikr_TEXTURE_2D &&
        texture->GetTexture()->GetTargetFormat() != vikr_TEXTURE_2D_MULTISAMPLE) {
      VikrLog::DisplayMessage(VIKR_WARNING, "RenderTarget is not of Texture2D format!");
    }
    m_colorAttachments[attachment] = texture->GetTexture();
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


vvoid GL4Framebuffer::Readbuffer(BufferMode mode) {
  glReadBuffer(GL4Framebuffer::GetFramebufferMode(mode));
}


vvoid GL4Framebuffer::Writebuffer(BufferMode mode) {
  glDrawBuffer(GL4Framebuffer::GetFramebufferMode(mode));
}


Texture *GL4Framebuffer::GetColorAttachment(vuint32 attachment) {
  if (m_colorAttachments.find(attachment) != m_colorAttachments.end()) {
    return m_colorAttachments[attachment];
  }
  return nullptr;
}


vvoid GL4Framebuffer::ClearAttachments() {
  for (auto i = m_colorAttachments.begin();
       i != m_colorAttachments.end();
        ++i)
  {
    ClearTexture(i->first);
  }
  m_colorAttachments.clear();
}
} // vikr