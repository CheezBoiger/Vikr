//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>
#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/graphics/gl4/gl4_renderpass.hpp>
#include <vikr/shader/glsl/gl4_texture2d.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>
#include <vikr/input/window.hpp>

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
  : m_read(BUFFER_NONE)
  , m_write(BUFFER_BACK)
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

  // Set up the Rendertargets.
  // Get the count on the number of RenderTargets.
  GLenum attachments[GL_MAX_COLOR_ATTACHMENTS];
  vuint32 count = 0;
  for (auto &val : m_renderPass->GetRenderTargets()) {
    GL4Texture *texture = static_cast<GL4Texture *>(val.second.GetTexture());
    if(texture->GetTargetFormat() != vikr_TARGET_2D &&
       texture->GetTargetFormat() != vikr_TARGET_2D_MULTISAMPLE) {
      VikrLog::DisplayMessage(VIKR_WARNING, "RenderTarget is not of Texture2D format!");
    }
    if (texture->GetNativeFormat() != GL_DEPTH_COMPONENT) {
      glFramebufferTexture2D(GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0 + val.first, texture->GetNativeTarget(), texture->GetNativeId(), 0);
      attachments[count] = GL_COLOR_ATTACHMENT0 + count;
      count++;
    } else {
      glFramebufferTexture2D(GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT, texture->GetNativeTarget(), texture->GetNativeId(), 0);
    }
    VIKR_ASSERT(glGetError() == 0);
  }
  glDrawBuffers(count, attachments);

  VIKR_ASSERT(glGetError() == 0);

  IsComplete();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);}


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
    GL4Texture *texture = static_cast<GL4Texture *>(i->second.GetTexture());
    if (texture->GetNativeFormat() == GL_DEPTH_COMPONENT) {
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    } else {
      if (texture->IsMultisampled()) {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
          GL_COLOR_ATTACHMENT0 + i->first, GL_TEXTURE_2D_MULTISAMPLE, 0, 0);
      } else {
        glFramebufferTexture2D(GL_FRAMEBUFFER, 
          GL_COLOR_ATTACHMENT0 + i->first, GL_TEXTURE_2D, 0, 0);
      }
    }
    VIKR_ASSERT(glGetError() == 0);
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


vvoid GL4Framebuffer::SetViewport(const Viewport &viewport) {
  m_viewport.win_x = viewport.win_x;
  m_viewport.win_y = viewport.win_y;
  m_viewport.win_width = viewport.win_width;
  m_viewport.win_height = viewport.win_height;
}


vbool GL4Framebuffer::HasDepthStencil() {
  for (auto &i : m_renderPass->GetRenderTargets()) {
    GL4Texture *texture = static_cast<GL4Texture *>(i.second.GetTexture());
    if (texture->GetNativeFormat() == GL_DEPTH_COMPONENT) {
      return true;
    }
  }
  return false;
}


vbool GL4Framebuffer::IsMultisampled() {
  for (auto &i : m_renderPass->GetRenderTargets()) {
    if (i.second.GetTexture()->IsMultisampled()) {
      return true;
    }
  }
  return false;
}


vvoid GL4Framebuffer::BlitTo(Framebuffer *framebuffer) {
  VIKR_ASSERT(glGetError() == 0);
  // nothing yet
  // will consider using glBlitFramebuffer
  GL4Framebuffer *glFb = static_cast<GL4Framebuffer *>(framebuffer);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
  VIKR_ASSERT(glGetError() == 0);
  if (framebuffer) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 
      static_cast<vuint32>(glFb->GetFramebufferId()));
    Viewport target = glFb->GetViewport();
    glDrawBuffer(GetFramebufferMode(m_write));
    glBlitFramebuffer(
      m_viewport.win_x, 
      m_viewport.win_y,
      m_viewport.win_width,
      m_viewport.win_height,
      target.win_x,
      target.win_y,
      target.win_width,
      target.win_height,
      GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
      GL_NEAREST
    );
    VIKR_ASSERT(glGetError() == 0);
  } else {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(
      m_viewport.win_x, m_viewport.win_y, m_viewport.win_width, m_viewport.win_height,
      0, 0, Window::GetMainWindow()->GetWidth(), Window::GetMainWindow()->GetHeight(),
      GL_DEPTH_BUFFER_BIT, GL_NEAREST
    );
    GLenum err = glGetError();
    VikrLog::DisplayMessage(VIKR_ERROR, std::to_string(err));
    VIKR_ASSERT(err == 0);
  }
}
} // vikr