//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/vk/vk_instance.hpp>
#include <graphics/vk/vk_device.hpp>

#include <util/vikr_log.hpp>


namespace vikr {


VkMemoryManager<VkInstance> VKInstance::instance = { vkDestroyInstance };


vvoid VKInstance::CreateInstance() {
  VkApplicationInfo app_info = { };
  VkInstanceCreateInfo inst_info = { };
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = VKDevice::kApplicationName;
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = VKDevice::kEngineName;
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

  if(vkCreateInstance(&inst_info, nullptr, instance.Replace()) != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Instance failed to create!");
  }
}
} // vikr