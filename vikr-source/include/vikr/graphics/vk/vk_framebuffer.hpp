//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_FRAMEBUFFER_HPP
#define __VIKR_VK_FRAMEBUFFER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


class VKRenderPass;

/**
  Vulkan Framebuffer implemenation.
*/
class VKFramebuffer : public Framebuffer {
public:
  /**
    Framebuffer constructor.
  */
  VKFramebuffer();

  vvoid Generate() override;

  vvoid SetClearColor(glm::vec3 color) override;
  glm::vec3 GetClearColor() override;

  VkFramebuffer GetFramebufferId() { return m_fbo.Get(); }

  vint32 IsComplete() override;
  
  vvoid Bind() override;
  vvoid Unbind() override;

  vvoid ClearAttachments() override;

  vvoid Update() override;

  vbool HasDepthStencil() override;

  vbool IsMultisampled() override;

  vvoid Readbuffer(BufferMode mode) override;

  vvoid Writebuffer(BufferMode mode) override;

  vvoid Cleanup() override;

  vvoid SetRenderPass(RenderPass *pass) override;

  RenderPass *GetRenderPass() override;

  Viewport GetViewport() override;

  vvoid SetViewport(const Viewport &viewport) override;

  vvoid BlitTo(Framebuffer *framebuffer) override;

private:

  glm::vec3 m_clearcolor                = glm::vec3(0.1f, 0.1f, 0.1f);

  VkMemoryManager<VkFramebuffer> m_fbo;

  VKRenderPass *m_renderPass            = nullptr;

  Viewport m_viewport;

  VkViewport m_native_viewport;
  VkRect2D m_native_scissor;
};
} // vikr
#endif // __VIKR_VK_FRAMEBUFFER_HPP