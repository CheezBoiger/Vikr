//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/vk/vk_phydevice.hpp>
#include <vikr/graphics/vk/vk_instance.hpp>
#include <vikr/graphics/vk/vk_surface.hpp>
#include <vikr/graphics/vk/vk_device.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>

#include <map>
#include <set>


namespace vikr {


VKPhysicalDevice::VKPhysicalDevice()
  : m_physicalDevice(VK_NULL_HANDLE)
  , m_currentCount(0)
  , device_ext({ VK_KHR_SWAPCHAIN_EXTENSION_NAME })
{
}



vvoid VKPhysicalDevice::CheckSuitableDevices(VKRenderDevice *rdevice) {
  vkEnumeratePhysicalDevices(rdevice->GetInstance().GetNativeInstance(), 
    &m_currentCount, nullptr);
  if (m_currentCount <= 0) {
    VikrLog::DisplayMessage(VIKR_ERROR, "No devices compatible with Vulkan found!");
    VIKR_DEBUG_BREAK();
  }
  m_foundDevices.resize(m_currentCount);
  vkEnumeratePhysicalDevices(rdevice->GetInstance().GetNativeInstance(), 
    &m_currentCount, m_foundDevices.data());
  for (VkPhysicalDevice &device : m_foundDevices) {
    if (IsSuitable(rdevice)) {
      m_physicalDevice = device;
      break;
    }
  } 
  if (m_physicalDevice == VK_NULL_HANDLE) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failed to find a Vulkan compatible GPU.");
    VIKR_DEBUG_BREAK();
  }
}


vbool VKPhysicalDevice::IsSuitable(VKRenderDevice *device) {
  VkPhysicalDeviceProperties properties = { };
  VkPhysicalDeviceFeatures features = { };
  VkPhysicalDeviceMemoryProperties memory_properties = { };
  VKQueueFamily family = VKQueueFamily::FindQueueFamilies(device);
  vkGetPhysicalDeviceProperties(device->GetPhysicalDevice().GetCurrentNativePhysicalDevice(), &properties);
  vkGetPhysicalDeviceFeatures(device->GetPhysicalDevice().GetCurrentNativePhysicalDevice(), &features);
  vkGetPhysicalDeviceMemoryProperties(device->GetPhysicalDevice().GetCurrentNativePhysicalDevice(), 
    &memory_properties);
  // Nothing with memory properties for now.

  vbool ext_supported = CheckDeviceExtensionSupport(
    device->GetPhysicalDevice().GetCurrentNativePhysicalDevice());

  return  properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && 
          family.IsComplete() && family.IsComplete() && ext_supported;
}


vbool VKPhysicalDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device) {
  vuint32 ext_count;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &ext_count, nullptr);
  std::vector<VkExtensionProperties> available_ext(ext_count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &ext_count, available_ext.data());
  std::set<std::string> req_ext(device_ext.begin(), device_ext.end());
  for (const auto &extension : available_ext) {
    req_ext.erase(extension.extensionName);
  }
  return req_ext.empty();
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


vint32 VKPhysicalDevice::RateDeviceCompatibility(VkPhysicalDevice device) {
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


VKQueueFamily VKQueueFamily::FindQueueFamilies(VKRenderDevice *device) {
  VKQueueFamily family;
  vuint32 queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device->GetPhysicalDevice().GetCurrentNativePhysicalDevice(), 
    &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_familes(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(device->GetPhysicalDevice().GetCurrentNativePhysicalDevice(), 
    &queue_family_count, queue_familes.data());
  vint32 i = 0;
  for (const auto &queue_family : queue_familes) {
    VkBool32 pSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device->GetPhysicalDevice().GetCurrentNativePhysicalDevice(), 
      i, device->GetSurface().GetNativeSurfaceKHR(), &pSupport);
    if (queue_family.queueCount > 0 && queue_family.queueFlags && VK_QUEUE_GRAPHICS_BIT && pSupport) {
      family.gfrFamily = i;
      family.prstFamily = i;
    }
    if (family.IsComplete()) {
      break;
    }
    i++;
  }
  return family;
}
} // vikr