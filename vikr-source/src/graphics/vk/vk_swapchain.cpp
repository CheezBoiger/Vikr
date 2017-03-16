//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/graphics/vk/vk_swapchain.hpp>
#include <vikr/graphics/vk/vk_surface.hpp>


namespace vikr {


vvoid VKSwapChain::Init(VkPhysicalDevice physical_device)
{
  device = physical_device;
}


SwapChainSupportDetails VKSwapChain::QuerySwapChainSupport()
{
  SwapChainSupportDetails details;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, VKSurface::surface, &details.capabilities);
  return details;
}
} // vikr