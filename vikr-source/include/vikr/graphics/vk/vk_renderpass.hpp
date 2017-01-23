//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_RENDERPASS_HPP
#define __VIKR_VK_RENDERPASS_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <vikr/graphics/render_pass.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>

#include <map>


namespace vikr {


/*
  Vulkan RenderPass implementation.
*/
class VKRenderPass : public RenderPass {
public:
  VKRenderPass();

  vvoid UpdateRenderTargets() override;

  vvoid Bind() override;

  vvoid Unbind() override;

  const Viewport &GetViewport() const override { return m_viewport; }

  vvoid SetViewport(Viewport viewport) override { 
    m_viewport = viewport;
  }

  glm::vec3 GetClearColor() const override { return m_clearcolor; }

  vbool AddRenderTarget(RenderTarget *target, vuint32 attachment) override;

  vbool RemoveRenderTarget(vuint32 attachment) override;

  RenderTarget *GetRenderTarget(vuint32 attachment) override;

private:
  
  VkMemoryManager<VkRenderPass> m_renderpass;

  /**
    The viewport of this render pass.
  */
  Viewport m_viewport;

  /**
    clear color.
  */
  glm::vec3 m_clearcolor;


  std::map<vuint32, RenderTarget *> m_rendertargets;
};
} // vikr
#endif // __VIKR_VK_RENDERPASS_HPP