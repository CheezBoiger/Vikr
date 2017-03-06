//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_VK_SWAPCHAIN_HPP
#define __VIKR_VK_SWAPCHAIN_HPP


#include <vikr/resources/vulkan/vk_memorymanager.hpp>

#include <vikr/graphics/graphics.hpp>


namespace vikr {


class VKSwapChain {
public:
  VKSwapChain();

  /**
    Gunna need that physical device to initialize yo...
  */
  vvoid Init(VkPhysicalDevice physical_dev);

private:
  
};
} // vikr
#endif // __VIKR_VK_SWAPCHAIN_HPP