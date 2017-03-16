//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/graphics/vk/vk_swapchain.hpp>
#include <vikr/graphics/vk/vk_surface.hpp>


namespace vikr {


vvoid VKSwapChain::Init(VKRenderDevice *renderdevice)
{
  device = renderdevice;
}


SwapChainSupportDetails VKSwapChain::QuerySwapChainSupport()
{
  SwapChainSupportDetails details;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    device->GetPhysicalDevice().GetCurrentNativePhysicalDevice(),
    device->GetSurface().GetNativeSurfaceKHR(),
    &details.capabilities);
  return details;
}
} // vikr