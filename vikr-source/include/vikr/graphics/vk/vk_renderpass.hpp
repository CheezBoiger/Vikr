//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_RENDERPASS_HPP
#define __VIKR_VK_RENDERPASS_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <vikr/graphics/render_pass.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>

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

private:
  
  VkMemoryManager<VkRenderPass> m_renderpass;
};
} // vikr
#endif // __VIKR_VK_RENDERPASS_HPP