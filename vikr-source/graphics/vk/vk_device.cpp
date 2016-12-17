//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/vk/vk_device.hpp>
#include <graphics/vk/vk_instance.hpp>
#include <graphics/vk/vk_phydevice.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


static const vchar *kApplicationName = "Vikr Software Application";
static const vchar *kEngineName = "Vikr Powered Graphics Engine";

vvoid VKDevice::Setup() {
  
}


vvoid VKDevice::CreateInstance() {
  VkApplicationInfo app_info;
  VkInstanceCreateInfo inst_info;
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = kApplicationName;
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = kEngineName;
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;
  
  inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  inst_info.pApplicationInfo = &app_info;
  vuint32 extension_count = 0;
  const vchar **extensions;
  extensions = glfwGetRequiredInstanceExtensions(&extension_count);
  inst_info.enabledExtensionCount = extension_count;
  inst_info.ppEnabledExtensionNames = extensions;
  inst_info.enabledLayerCount = 0;

  if (vkCreateInstance(&inst_info, nullptr, instance.Replace()) != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Instance failed to create!");
  }
}


vvoid VKDevice::DeterminePhysicalDevice() {
  VKPhysicalDevice::CheckSuitableDevices(instance.Get());
  VKPhysicalDevice::SelectPhysicalDevice();
  physical_device = VKPhysicalDevice::GetCurrentDevice();
}


vvoid VKDevice::CreateLogicalDevices() {
  VKQueueFamily indices = VKQueueFamily::FindQueueFamilies(physical_device);
  VkDeviceQueueCreateInfo queue_info;
  vreal32 priority = 1.0f;
  queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_info.queueFamilyIndex = indices.GetGFRFamily();
  queue_info.queueCount = 1;
  queue_info.pQueuePriorities = &priority;

  VkPhysicalDeviceFeatures device_features;

  VkDeviceCreateInfo device_info;
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.pQueueCreateInfos = &queue_info;
  device_info.queueCreateInfoCount = 1;
  device_info.pEnabledFeatures = &device_features;
  device_info.enabledExtensionCount = false;
  // For debuggin purposes, we'll leave it out for not. This will 
  // require Validation Layers in the future. 
  device_info.enabledLayerCount = false; 

  if (vkCreateDevice(physical_device, &device_info, nullptr, device.Replace()) != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failed to create a logical device!");
  }

  vkGetDeviceQueue(device, indices.GetGFRFamily(), 0, &context.GetGraphicsQueue());
}


vvoid VKDevice::CreateSurface() {
}
} // vikr