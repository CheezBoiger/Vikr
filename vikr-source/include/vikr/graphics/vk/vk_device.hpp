//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_DEVICE_HPP
#define __VIKR_VK_DEVICE_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/graphics/vk/vk_context.hpp>
#include <vikr/graphics/vk/vk_phydevice.hpp>
#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>
#include <vikr/resources/vulkan/vk_resource_manager.hpp>
#include <vikr/shader/cubemap.hpp>


namespace vikr {


/**
  Vulkan RenderDevice. Initializing the Renderer with this device
  will enable the GPU to issue Vulkan Commands and requests.
  
  This is still in developement however, so be on the look out to figure out 
  what to do.

  TODO(): This device is currently not usable, work is being done however.
*/
class VKDevice : public RenderDevice {
public:
  VKDevice();

  std::string GetShaderLanguage() override;

  Texture *GenerateTexture(std::string path, 
    TextureTarget target, vbool alpha) override;

  Framebuffer *CreateFramebuffer() override;

  Material *CreateMaterial(std::string name) override;
  
  Vertexbuffer *CreateVertexbuffer(VertexContainer &vertices) override;

  ResourceManager *GetResourceManager() override;

  RenderContext *GetContext() override { return &context; }

  Cubemap *CreateCubemap() override;

  RenderPass *CreateRenderPass() override;

  Commandbuffer &CreateCommandbuffer(CommandbufferList *list) override;

  VkDevice GetVkDevice() { return m_logicDevice.Get(); }

  vbool DestroyVertexbuffer(guid_t id) override;
  vbool DestroyCubemap(guid_t id) override;
  vbool DestroyRenderPass(guid_t id) override;
  vbool DestroyCommandbufferList(guid_t id) override;


  CommandbufferList *CreateCommandbufferList() override;

private:

  vvoid Setup();

  vvoid DeterminePhysicalDevice();

  vvoid CreateLogicalDevices();
  
  /**
    Vulkan Logic Device.
  */
  VkMemoryManager<VkDevice> m_logicDevice;
  
  VKPhysicalDevice m_physicalDevice;

  /**
    Vulkan Context.
  */
  VKContext context;

  VKResourceManager manager;

public:
  static const vchar *kApplicationName;
  static const vchar *kEngineName;
};
} // vikr
#endif // __VIKR_VK_DEVICE_HPP