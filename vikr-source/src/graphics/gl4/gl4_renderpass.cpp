//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_renderpass.hpp>

#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>


namespace vikr {


vvoid GL4RenderPass::UpdateRenderTargets() {
  if(m_framebuffer) {
    m_framebuffer->Bind();
    // Clear up last RenderPass in Framebuffer.
    m_framebuffer->ClearAttachments();
    // Set up the new RenderPass
    for(vuint32 i = 0; i < m_rendertargets.size(); ++i) {
      if(m_rendertargets[i]->GetRenderType() == RenderTargetType::render_TEXTURE) {
        m_framebuffer->BindTexture(m_rendertargets[i], i);
      }
    }
    m_framebuffer->Validate();
    if(m_renderbuffer) {
      m_framebuffer->BindDepthStencilBuffer(m_renderbuffer);
    }
    if(!m_framebuffer->IsComplete()) {
      VikrLog::DisplayMessage(VIKR_ERROR, "Framebuffer is not complete!");
    }
    m_framebuffer->Unbind();
  }
}


vvoid GL4RenderPass::Bind() {
  if(m_framebuffer) {
    m_framebuffer->Bind();
  }
}


vvoid GL4RenderPass::Unbind() {
  if(m_framebuffer) {
    m_framebuffer->Unbind();
  }
}


vbool GL4RenderPass::AddRenderTarget(RenderTarget *target, vuint32 attachment) {
  if (m_rendertargets.find(attachment) == m_rendertargets.end()) {
    m_rendertargets[attachment] = target;
    return true;
  }
  return false;
}


vbool GL4RenderPass::RemoveRenderTarget(vuint32 attachment) {
  if (m_rendertargets.find(attachment) == m_rendertargets.end()) {
    m_rendertargets.erase(attachment);
    return true;
  }
  return false;
}


RenderTarget *GL4RenderPass::GetRenderTarget(vuint32 attachment) {
  if (m_rendertargets.find(attachment) != m_rendertargets.end()) {
    return m_rendertargets[attachment];
  }
  return nullptr;
}
} // vikr