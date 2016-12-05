//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/vulkan/vkrenderer.hpp>
#include <util/vikr_log.hpp>
#include <util/vikr_assert.hpp>


namespace vikr {


vint32 VkRenderer::Init() {
  CreateInstance();
  return true;  
}


vvoid VkRenderer::Render() {
}


vvoid VkRenderer::CreateInstance() {
  VkApplicationInfo app_info {
    VK_STRUCTURE_TYPE_APPLICATION_INFO,
    nullptr,
    "Vikr Renderer Application",
    VK_MAKE_VERSION(1, 0, 0),
    "Vikr Vulkan Renderer",
    VK_MAKE_VERSION(1, 0, 0),
    VK_API_VERSION_1_0
  };
  VkInstanceCreateInfo instance_info;
  instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_info.pApplicationInfo = &app_info;
  vuint32 extension_count = 0;
  const char **extenstions = glfwGetRequiredInstanceExtensions(&extension_count);
  instance_info.enabledLayerCount = 0;
  VkResult result = vkCreateInstance(&instance_info, nullptr, instance.Replace());
  if (result != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failed to Create vk instance!");
    VIKR_DEBUG_BREAK();
  }
}
} // vikr