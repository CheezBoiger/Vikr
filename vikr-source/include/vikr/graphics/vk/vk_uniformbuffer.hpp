//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_UNIFORMBUFFER_HPP
#define __VIKR_VK_UNIFORMBUFFER_HPP


#include <vikr/graphics/uniformbuffer.hpp>
#include <vikr/graphics/vk/vk_device.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>
#include <vikr/graphics/graphics.hpp>


namespace vikr {


class VKUniformbuffer {
public:
  VKUniformbuffer();

private:
  VkMemoryManager<VkBuffer> stagingBuffer;
  VkMemoryManager<VkBuffer> uniformBuffer;
  VkMemoryManager<VkDeviceMemory> stagingMem;
  VkMemoryManager<VkDeviceMemory> uniformMem;
};
} // vikr
#endif // __VIKR_VK_UNIFORMBUFFER_HPP 