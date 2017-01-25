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

  std::unique_ptr<Framebuffer> CreateFramebuffer() override;

  Shader *GetShader(std::string name) override;

  vvoid StoreShader(
    std::string name,
    std::string vs,
    std::string fs,
    std::string include = ".",
    std::string gs = "") override;

  Material *CreateMaterial(std::string name) override;
  
  std::unique_ptr<Vertexbuffer> CreateVertexbuffer(VertexContainer &vertices) override;

  ResourceManager *GetResourceManager() override;

  RenderContext *GetContext() override { return &context; }

  std::unique_ptr<RenderTexture> CreateRenderTexture(std::string t_name, vuint32 width, vuint32 height,
    vbool alpha = false, vbool multisample = false, DataTypeFormat precision = data_UNSIGNED_BYTE) override;

  std::unique_ptr<Renderbuffer> CreateRenderbuffer(vuint32 width, vuint32 height, vbool multisample = false) override;

  std::unique_ptr<Cubemap> CreateCubemap() override;

  std::unique_ptr<RenderPass> CreateRenderPass() override;

  std::unique_ptr<Commandbuffer> CreateCommandbuffer() override;


private:

  vvoid Setup();

  vvoid DeterminePhysicalDevice();

  vvoid CreateLogicalDevices();
  
  VkMemoryManager<VkDevice> device      { vkDestroyDevice };

  VKContext context;

public:
  static const vchar *kApplicationName;
  static const vchar *kEngineName;
};
} // vikr
#endif // __VIKR_VK_DEVICE_HPP