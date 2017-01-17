//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_VK_INSTANCE_HPP
#define __VIKR_VK_INSTANCE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>

namespace vikr {


/**
  Instance device which is specified by the vulkan device.
*/
class VKInstance {
public:

  static vvoid CreateInstance();


  static VkMemoryManager<VkInstance> instance;

};
} // vikr
#endif // __VIKR_VK_INSTANCE_HPP