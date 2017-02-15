//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>
#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/graphics/gl4/gl4_renderpass.hpp>
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
    glViewport(
      m_viewport.win_x,
      m_viewport.win_y,
      m_viewport.win_width,
      m_viewport.win_height
    );
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


vvoid GL4Framebuffer::Update() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  // Renderbuffer binding.
  ClearAttachments();
  if (m_renderPass->GetRenderbuffer()) {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
      GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 
      m_renderPass->GetRenderbuffer()->GetRenderbufferId()
    );
  }

  // Set up the Rendertargets.
  for (auto val : m_renderPass->GetRenderTargets()) {
    GL4RenderTexture *texture = static_cast<GL4RenderTexture *>(val.second);
    if(texture->GetTexture()->GetTargetFormat() != vikr_TEXTURE_2D &&
       texture->GetTexture()->GetTargetFormat() != vikr_TEXTURE_2D_MULTISAMPLE) {
      VikrLog::DisplayMessage(VIKR_WARNING, "RenderTarget is not of Texture2D format!");
    }
    GLTexture *gl = static_cast<GLTexture2D *>(texture->GetTexture());
    glFramebufferTexture2D(GL_FRAMEBUFFER,
      GL_COLOR_ATTACHMENT0 + val.first, gl->GetNativeTarget(), gl->GetNativeId(), 0);
  }

  // Get the count on the number of RenderTargets.
  GLenum attachments[GL_MAX_COLOR_ATTACHMENTS];
  vuint32 count = 0;
  while (count < m_renderPass->GetNumOfRenderTargets()) {
    attachments[count] = GL_COLOR_ATTACHMENT0 + count;
    count++;
  }
  glDrawBuffers(count, attachments);
  IsComplete();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


vvoid GL4Framebuffer::Readbuffer(BufferMode mode) {
  glReadBuffer(GL4Framebuffer::GetFramebufferMode(mode));
}


vvoid GL4Framebuffer::Writebuffer(BufferMode mode) {
  glDrawBuffer(GL4Framebuffer::GetFramebufferMode(mode));
}


vvoid GL4Framebuffer::ClearAttachments() {
  auto structure = m_renderPass->GetRenderTargets();
  for (auto i = structure.begin();
       i != structure.end();
        ++i)
  {
    if (i->second->IsMultisampled()) {
      glFramebufferTexture2D(GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0 + i->first, GL_TEXTURE_2D_MULTISAMPLE, 0, 0);
    } else {
      glFramebufferTexture2D(GL_FRAMEBUFFER, 
        GL_COLOR_ATTACHMENT0 + i->first, GL_TEXTURE_2D, 0, 0);
    }
  }
}


vvoid GL4Framebuffer::Cleanup() {
  if (m_fbo) {
    glDeleteFramebuffers(1, &m_fbo);
  }
}


RenderPass *GL4Framebuffer::GetRenderPass() {
  return static_cast<RenderPass *>(m_renderPass);
}


vvoid GL4Framebuffer::SetRenderPass(RenderPass *pass) {
  m_renderPass = static_cast<GL4RenderPass *>(pass);
}


vvoid GL4Framebuffer::SetViewport(Viewport &viewport) {
  m_viewport.win_x = viewport.win_x;
  m_viewport.win_y = viewport.win_y;
  m_viewport.win_width = viewport.win_width;
  m_viewport.win_height = viewport.win_height;
}


vbool GL4Framebuffer::HasDepthStencil() {
  if (m_renderPass && m_renderPass->GetRenderbuffer()) {
    return true;
  }
  return false;
}


vbool GL4Framebuffer::IsMultisampled() {
  if (m_renderPass && m_renderPass->GetRenderbuffer() 
    && m_renderPass->GetRenderbuffer()->IsMultisampled()) {
    return true;
  }
  return false;
}


vvoid GL4Framebuffer::BlitTo(Framebuffer *framebuffer) {
  // nothing yet
  // will consider using glBlitFramebuffer
}
} // vikr