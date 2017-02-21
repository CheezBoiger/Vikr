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
  VkPhysicalDeviceFeatures device_features;
  
  std::vector<VkDeviceQueueCreateInfo> queue_createInfos;
  std::set<vint32> unique_queueFamilies =  { indices.GetGFRFamily(), indices.GetPrstFamily()};

  vreal32 priority = 1.0f;
  for (vint32 queueFamily : unique_queueFamilies) {
    VkDeviceQueueCreateInfo queue_info;
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = queueFamily;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = &priority;
    queue_createInfos.push_back(queue_info);
  }

  VkDeviceCreateInfo device_info;
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.pQueueCreateInfos = queue_createInfos.data();
  device_info.queueCreateInfoCount = (vuint32) queue_createInfos.size();
  device_info.pEnabledFeatures = &device_features;
  device_info.enabledExtensionCount = false;
  // For debuggin purposes, we'll leave it out for now. This will 
  // require Validation Layers in the future. 
  device_info.enabledLayerCount = false; 

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


Texture *VKDevice::GenerateTexture(std::string path, TextureTarget target, vbool alpha) {
  return nullptr;
}


std::unique_ptr<Framebuffer> VKDevice::CreateFramebuffer() {
  return nullptr;
}


Material *VKDevice::CreateMaterial(std::string name) {
  return nullptr;
}


std::unique_ptr<Vertexbuffer> VKDevice::CreateVertexbuffer(VertexContainer &vertices) {
  return nullptr;
}


ResourceManager *VKDevice::GetResourceManager() {
  return nullptr;
}


std::unique_ptr<RenderTexture> VKDevice::CreateRenderTexture(std::string t_name,
  vuint32 width, vuint32 height, vbool alpha, vbool multisample, DataTypeFormat precision) {
  return nullptr;
}


std::unique_ptr<Renderbuffer> VKDevice::CreateRenderbuffer(vuint32 width, vuint32 height, vbool multisample) {
  return nullptr;
}


std::unique_ptr<Cubemap> VKDevice::CreateCubemap() {
  return nullptr;
}
} // vikr