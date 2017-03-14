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


const vchar *VKRenderDevice::kApplicationName = "Vikr Software Application";
const vchar *VKRenderDevice::kEngineName = "Vikr Powered Graphics Engine";
const std::string kShaderLanguage = "Spir-V";


VKRenderDevice::VKRenderDevice()
  : RenderDevice(vikr_API_VULKAN)
{
  Setup();
}

// Pipeline setup.
vvoid VKRenderDevice::Setup() {
  VKInstance::CreateInstance();
  VKSurface::CreateSurface();
  DeterminePhysicalDevice();
  CreateLogicalDevices();
}


vvoid VKRenderDevice::DeterminePhysicalDevice() {
  m_physicalDevice.CheckSuitableDevices(VKInstance::instance.Get());
  m_physicalDevice.SelectPhysicalDevice();
}


vvoid VKRenderDevice::CreateLogicalDevices() {
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


std::string VKRenderDevice::GetShaderLanguage() {
  return kShaderLanguage;
}


Framebuffer *VKRenderDevice::CreateFramebuffer() {
  return nullptr;
}


Vertexbuffer *VKRenderDevice::CreateVertexbuffer(VertexUsageType type, 
  std::vector<Vertex> &vertices, std::vector<vuint32> &indices) 
{
  return nullptr;
}


Cubemap *VKRenderDevice::CreateCubemap() {
  return nullptr;
}


RenderPass *VKRenderDevice::CreateRenderPass() {
  return nullptr;
}


Commandbuffer &VKRenderDevice::CreateCommandbuffer() {
  throw new std::bad_alloc();
}


vbool VKRenderDevice::DestroyVertexbuffer(guid_t id) {
  return false;
}


vbool VKRenderDevice::DestroyCubemap(guid_t id) {
  return false;
}


vbool VKRenderDevice::DestroyRenderPass(guid_t id) {
  return false;
}


vbool VKRenderDevice::DestroyFramebuffer(guid_t id) {
  return false;
}


Shader *VKRenderDevice::CreateShader(std::string name, ShaderStage stage) {
  return nullptr;
}


Shader *VKRenderDevice::GetShader(guid_t id) {
  return nullptr;
}


vbool VKRenderDevice::DestroyShader(guid_t id) {
  return false;
}


GraphicsPipelineState *VKRenderDevice::CreateGraphicsPipelineState(vbool derivative) {
  return nullptr;
}


GraphicsPipelineState *VKRenderDevice::GetGraphicsPipelineState(guid_t id) {
  return nullptr;
}


vbool VKRenderDevice::DestroyGraphicsPipelineState(guid_t id) {
  return false;
}


Texture *VKRenderDevice::CreateTexture(
  std::string name,
  TextureTarget target,
  std::string img_path,
  vbool alpha)
{
  return nullptr;
}


Texture *VKRenderDevice::GetTexture(guid_t id) {
  return nullptr;
}


vbool VKRenderDevice::DestroyTexture(guid_t id) {
  return false;
}


vbool VKRenderDevice::DestroyUniformbuffer(guid_t id) {
  return false;
}


Uniformbuffer *VKRenderDevice::GetUniformbuffer(guid_t id) {
  return nullptr;
}


Uniformbuffer *VKRenderDevice::CreateUniformbuffer() {
  return nullptr;
}


ComputePipelineState *VKRenderDevice::CreateComputePipelineState(std::string name) {
  return nullptr;
}


ComputePipelineState *VKRenderDevice::GetComputePipelineState(guid_t id) {
  return nullptr;
}


vbool VKRenderDevice::DestroyComputePipelineState(guid_t id) {
  return false;
}


GraphicsHardwareInfo VKRenderDevice::GetHardwareInformation() {
  GraphicsHardwareInfo info = { };

  return info;
}


GraphicsPerformanceInfo VKRenderDevice::GetPerformanceInformation() {
  GraphicsPerformanceInfo info;

  return info;
}
} // vikr