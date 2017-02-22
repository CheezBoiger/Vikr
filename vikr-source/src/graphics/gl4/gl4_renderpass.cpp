//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_renderpass.hpp>

#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>


namespace vikr {


vbool GL4RenderPass::AddRenderTarget(RenderTarget target, vuint32 attachment) {
  if (m_rendertargets.find(attachment) == m_rendertargets.end()) {
    m_rendertargets[attachment] = std::move(target);
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
    return &m_rendertargets[attachment];
  }
  return nullptr;
}
} // vikr