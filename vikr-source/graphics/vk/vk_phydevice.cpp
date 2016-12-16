//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/vk/vk_phydevice.hpp>
#include <util/vikr_log.hpp>
#include <util/vikr_assert.hpp>
#include <map>

namespace vikr {


vuint32 VKPhysicalDevice::m_currentCount = 0;
std::vector<VkPhysicalDevice> VKPhysicalDevice::m_foundDevices;
VkPhysicalDevice VKPhysicalDevice::m_physicalDevice = VK_NULL_HANDLE;


vvoid VKPhysicalDevice::CheckSuitableDevices(VkInstance &instance) {
  vkEnumeratePhysicalDevices(instance, &m_currentCount, nullptr);
  if (m_currentCount <= 0) {
    VikrLog::DisplayMessage(VIKR_ERROR, "No devices compatible with Vulkan found!");
    VIKR_DEBUG_BREAK();
  }
  m_foundDevices.resize(m_currentCount);
  vkEnumeratePhysicalDevices(instance, &m_currentCount, m_foundDevices.data());
  for (VkPhysicalDevice &device : m_foundDevices) {
    if (IsSuitable(device)) {
      m_physicalDevice = device;
      break;
    }
  } 
  if (m_physicalDevice == VK_NULL_HANDLE) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failed to find a Vulkan compatible GPU.");
    VIKR_DEBUG_BREAK();
  }
}


vbool VKPhysicalDevice::IsSuitable(VkPhysicalDevice &device) {
  VkPhysicalDeviceProperties properties;
  VkPhysicalDeviceFeatures features;
  VkPhysicalDeviceMemoryProperties memory_properties;
  VKQueueFamily family = VKQueueFamily::FindQueueFamilies(device);
  vkGetPhysicalDeviceProperties(device, &properties);
  vkGetPhysicalDeviceFeatures(device, &features);
  vkGetPhysicalDeviceMemoryProperties(device, &memory_properties);
  // Nothing with memory properties for now.
  return  properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && 
          features.geometryShader && 
          family.IsComplete();
}


vvoid VKPhysicalDevice::SelectPhysicalDevice() {
  std::map<vint32, VkPhysicalDevice> candidates;
  for (VkPhysicalDevice &device : m_foundDevices) {
    vint32 score = RateDeviceCompatibility(device);
    candidates[score] = device;
  }
  if (candidates.begin()->first > 0) {
    m_physicalDevice = candidates.begin()->second;
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "Could not find a compatible Vulkan GPU.");
    VIKR_DEBUG_BREAK();
  }
}


vint32 VKPhysicalDevice::RateDeviceCompatibility(VkPhysicalDevice &device) {
  VkPhysicalDeviceProperties properties;
  VkPhysicalDeviceFeatures features;
  VkPhysicalDeviceMemoryProperties memory_properties;
  vkGetPhysicalDeviceProperties(device, &properties);
  vkGetPhysicalDeviceFeatures(device, &features);
  vkGetPhysicalDeviceMemoryProperties(device, &memory_properties);
  vint32 score = 0;
  if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
    score += 1000;
  }
  score += properties.limits.maxImageDimension2D;
  if (!features.geometryShader) {
    score = 0;
  }
  return score;
}


VKQueueFamily VKQueueFamily::FindQueueFamilies(VkPhysicalDevice device) {
  VKQueueFamily family;
  vuint32 queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_familes(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_familes.data());
  vint32 i = 0;
  for (const auto &queue_family : queue_familes) {
    if (queue_family.queueCount > 0 && queue_family.queueFlags && VK_QUEUE_GRAPHICS_BIT) {
      family.gfrFamily = i;
    }
    if (family.IsComplete()) {
      break;
    }
    i++;
  }
  return family;
}
} // vikr