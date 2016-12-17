//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_DEVICE_HPP
#define __VIKR_VK_DEVICE_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <graphics/render_device.hpp>
#include <graphics/vk/vk_context.hpp>
#include <graphics/vk/vk_phydevice.hpp>
#include <resources/vulkan/vk_memorymanager.hpp>

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
  
  std::unique_ptr<Vertexbuffer> CreateVertexbuffer(std::vector<Vertex> &vertices,
    std::vector<vuint32> &indices, VertexUsageType type) override;

  ResourceManager *GetResourceManager() override;

  RenderContext *GetContext() override { return &context; }

  std::unique_ptr<RenderTexture> CreateRenderTexture(std::string t_name, vuint32 width, vuint32 height,
    vbool alpha = false, DataTypeFormat precision = data_UNSIGNED_BYTE) override;

  std::unique_ptr<Renderbuffer> CreateRenderbuffer(vuint32 width, vuint32 height) override;

  std::unique_ptr<Cubemap> CreateCubemap() override;


private:

  vvoid Setup();

  vvoid CreateInstance();

  vvoid DeterminePhysicalDevice();

  vvoid CreateLogicalDevices();

  vvoid CreateSurface();
  

  VkPhysicalDevice physical_device      { VK_NULL_HANDLE };
  VkMemoryManager<VkInstance> instance  { vkDestroyInstance };
  VkMemoryManager<VkDevice> device      { vkDestroyDevice };
  VkMemoryManager<VkSurfaceKHR> surface { instance, vkDestroySurfaceKHR}; 

  VKContext context;
};
} // vikr
#endif // __VIKR_VK_DEVICE_HPP