//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_RENDERPASS_HPP
#define __VIKR_VK_RENDERPASS_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/graphics.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>

#include <map>


namespace vikr {


class VKRenderDevice;



/// Vulkan RenderPass implementation.
class VKRenderPass : public RenderPass {
public:
  VKRenderPass();


  VkRenderPass GetNativePass() {return m_renderpass.Get(); }

private:
  VKRenderDevice *device; 
  VkMemoryManager<VkRenderPass> m_renderpass;

  std::map<vuint32, RenderTarget> m_rendertargets;
};
} // vikr
#endif // __VIKR_VK_RENDERPASS_HPP