//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_VK_SWAPCHAIN_HPP
#define __VIKR_VK_SWAPCHAIN_HPP


#include <vikr/resources/vulkan/vk_memorymanager.hpp>
#include <vikr/graphics/vk/vk_device.hpp>
#include <vikr/graphics/graphics.hpp>


namespace vikr {


struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentation_modes;
};


class VKSwapChain {
public:
  VKSwapChain();

  /**
    Gunna need that physical device to initialize yo...
  */
  vvoid Init(VKRenderDevice *device);

  SwapChainSupportDetails QuerySwapChainSupport();

private:
  VKRenderDevice *device;
};
} // vikr
#endif // __VIKR_VK_SWAPCHAIN_HPP