//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_SURFACE_HPP
#define __VIKR_VK_SURFACE_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <vikr/resources/vulkan/vk_memorymanager.hpp>

#include <vikr/graphics/graphics.hpp>

namespace vikr {


class VKSurface {
public:

  static vvoid CreateSurface();

  static VkMemoryManager<VkSurfaceKHR> surface;
}; 
} // vikr
#endif // __VIKR_VK_SURFACE_HPP