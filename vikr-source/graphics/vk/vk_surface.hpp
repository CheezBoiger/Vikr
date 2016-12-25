//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_SURFACE_HPP
#define __VIKR_VK_SURFACE_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


class VKSurface {
public:

  static vvoid CreateSurface();

  static VkMemoryManager<VkSurfaceKHR> surface;
}; 
} // vikr
#endif // __VIKR_VK_SURFACE_HPP