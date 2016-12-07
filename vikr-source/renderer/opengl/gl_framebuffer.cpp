//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/opengl/gl_framebuffer.hpp>
#include <util/vikr_log.hpp>
#include <util/vikr_assert.hpp>
#include <renderer/render_target.hpp>

namespace vikr {


vvoid GLFramebuffer::Generate() {
  if(!m_fbo) {
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  }

  if(!m_rbo) {
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(
      GL_RENDERBUFFER, 
      VIKR_DEPTH24_STENCIL8, 
      m_width, 
      m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
  }
}


vvoid GLFramebuffer::Bind() {
  if(m_fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  }
}


vvoid GLFramebuffer::Unbind() {
  if(m_fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}


vint32 GLFramebuffer::IsComplete() {
  vbool success = false;
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    VikrLog::DisplayMessage(VIKR_WARNING, "Framebuffer is not complete!"); 
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return false;
  }
  return true;
}


vvoid GLFramebuffer::BindTexture(RenderTarget *target, vuint32 index) {
  if (target) {
    glFramebufferTexture2D(
      GL_FRAMEBUFFER,
      GL_COLOR_ATTACHMENT0 + index, 
      GL_TEXTURE_2D, 
      target->GetTexture()->GetNativeId(), 0);
    m_colorAttachments.push_back(target->GetTexture());
  }
}



} // vikr