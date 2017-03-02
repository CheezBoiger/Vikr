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

  vbool AddRenderTarget(RenderTarget target, vuint32 attachment) override;

  vbool RemoveRenderTarget(vuint32 attachment) override;

  RenderTarget *GetRenderTarget(vuint32 attachment) override;

  VkRenderPass GetNativePass() {return m_renderpass.Get(); }

private:
  
  VkMemoryManager<VkRenderPass> m_renderpass;

  std::map<vuint32, RenderTarget> m_rendertargets;
};
} // vikr
#endif // __VIKR_VK_RENDERPASS_HPP