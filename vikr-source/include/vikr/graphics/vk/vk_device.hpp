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
#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>
#include <vikr/shader/cubemap.hpp>

#include <vikr/graphics/graphics.hpp>


namespace vikr {


/**
  Vulkan RenderDevice. Initializing the Renderer with this device
  will enable the GPU to issue Vulkan Commands and requests.
  
  This is still in developement however, so be on the look out to figure out 
  what to do.

  TODO(): This device is currently not usable, work is being done however.
*/
class VKRenderDevice : public RenderDevice {
public:
  VKRenderDevice();

  std::string GetShaderLanguage() override;

  Framebuffer *CreateFramebuffer() override;
  
  Vertexbuffer *CreateVertexbuffer(VertexUsageType type, 
    std::vector<Vertex> &vertices, std::vector<vuint32> &indices= std::vector<vuint32>()) override;

  RenderContext *GetContext() override { return &context; }

  Cubemap *CreateCubemap() override;

  RenderPass *CreateRenderPass() override;

  Commandbuffer &CreateCommandbuffer() override;

  VkDevice GetVkDevice() { return m_logicDevice.Get(); }

  vbool DestroyVertexbuffer(guid_t id) override;
  vbool DestroyCubemap(guid_t id) override;
  vbool DestroyRenderPass(guid_t id) override;
  vbool DestroyFramebuffer(guid_t id) override;

  vbool DestroyUniformbuffer(guid_t id) override;
  Uniformbuffer *CreateUniformbuffer() override;
  Uniformbuffer *GetUniformbuffer(guid_t id) override;

  GraphicsPipelineState *CreateGraphicsPipelineState(vbool derivative) override;
  GraphicsPipelineState *GetGraphicsPipelineState(guid_t id) override;
  vbool DestroyGraphicsPipelineState(guid_t id) override;

  ComputePipelineState *CreateComputePipelineState(std::string name) override;
  ComputePipelineState *GetComputePipelineState(guid_t id) override;
  vbool DestroyComputePipelineState(guid_t id) override;

  /**
  Create a shader, and store it into Resources, the id of the shader will
  be returned. Resources takes care of this.
  */
  Shader *CreateShader(std::string name, ShaderStage stage) override;
  Shader *GetShader(guid_t id) override;
  vbool DestroyShader(guid_t id) override;

  Texture *CreateTexture(std::string name, TextureTarget target,
                         std::string filepath, vbool alpha) override;
  Texture *GetTexture(guid_t id) override;
  vbool DestroyTexture(guid_t id) override;

  GraphicsHardwareInfo GetHardwareInformation() override;
  GraphicsPerformanceInfo GetPerformanceInformation() override;

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
  VKRenderContext context;

public:
  static const vchar *kApplicationName;
  static const vchar *kEngineName;
};
} // vikr
#endif // __VIKR_VK_DEVICE_HPP