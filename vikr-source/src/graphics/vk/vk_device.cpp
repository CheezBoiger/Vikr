//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/vk/vk_device.hpp>
#include <vikr/graphics/vk/vk_instance.hpp>
#include <vikr/graphics/vk/vk_phydevice.hpp>
#include <vikr/graphics/vk/vk_surface.hpp>
#include <vikr/util/vikr_log.hpp>

#include <vikr/input/window.hpp>

#include <set>
#include <vector>


namespace vikr {


const vchar *VKDevice::kApplicationName = "Vikr Software Application";
const vchar *VKDevice::kEngineName = "Vikr Powered Graphics Engine";
const std::string kShaderLanguage = "Spir-V";


VKDevice::VKDevice()
{
  Setup();
}

// Pipeline setup.
vvoid VKDevice::Setup() {
  VKInstance::CreateInstance();
  VKSurface::CreateSurface();
  DeterminePhysicalDevice();
  CreateLogicalDevices();
}


vvoid VKDevice::DeterminePhysicalDevice() {
  m_physicalDevice.CheckSuitableDevices(VKInstance::instance.Get());
  m_physicalDevice.SelectPhysicalDevice();
}


vvoid VKDevice::CreateLogicalDevices() {
  VKQueueFamily indices = 
    VKQueueFamily::FindQueueFamilies(m_physicalDevice.GetCurrentDevice());
  VkPhysicalDeviceFeatures device_features = { };
  
  std::vector<VkDeviceQueueCreateInfo> queue_createInfos;
  std::set<vint32> unique_queueFamilies =  { indices.GetGFRFamily(), indices.GetPrstFamily()};

  vreal32 priority = 1.0f;
  for (vint32 queueFamily : unique_queueFamilies) {
    VkDeviceQueueCreateInfo queue_info = { };
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = queueFamily;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = &priority;
    queue_createInfos.push_back(queue_info);
  }

  VkDeviceCreateInfo device_info = { };
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.pQueueCreateInfos = queue_createInfos.data();
  device_info.queueCreateInfoCount = (vuint32 )queue_createInfos.size();
  device_info.pEnabledFeatures = &device_features;
  // Enable extensions here.
  device_info.enabledExtensionCount = m_physicalDevice.GetDeviceExtensions().size();
  device_info.ppEnabledExtensionNames = m_physicalDevice.GetDeviceExtensions().data();
  // For debuggin purposes, we'll leave it out for now. This will 
  // require Validation Layers in the future. 
  device_info.enabledLayerCount = 0; 

  if (vkCreateDevice(m_physicalDevice.GetCurrentDevice(),
        &device_info, nullptr, m_logicDevice.Replace()) != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failed to create a logical device!");
  }

  vkGetDeviceQueue(m_logicDevice, indices.GetGFRFamily(), 0, &context.GetGraphicsQueue());
  vkGetDeviceQueue(m_logicDevice, indices.GetPrstFamily(), 0, &context.GetPresentationQueue());
}


std::string VKDevice::GetShaderLanguage() {
  return kShaderLanguage;
}


Framebuffer *VKDevice::CreateFramebuffer() {
  return nullptr;
}


Vertexbuffer *VKDevice::CreateVertexbuffer(VertexContainer &vertices) {
  return nullptr;
}


ResourceManager *VKDevice::GetResourceManager() {
  return nullptr;
}


Cubemap *VKDevice::CreateCubemap() {
  return nullptr;
}


RenderPass *VKDevice::CreateRenderPass() {
  return nullptr;
}


Commandbuffer &VKDevice::CreateCommandbuffer(CommandbufferList *list) {
  throw new std::bad_alloc();
}


CommandbufferList *VKDevice::CreateCommandbufferList() {
  return nullptr;
}

vbool VKDevice::DestroyVertexbuffer(guid_t id) {
  return false;
}


vbool VKDevice::DestroyCubemap(guid_t id) {
  return false;
}


vbool VKDevice::DestroyRenderPass(guid_t id) {
  return false;
}


vbool VKDevice::DestroyCommandbufferList(guid_t id) {
  return false;
}


vbool VKDevice::DestroyFramebuffer(guid_t id) {
  return false;
}
} // vikr