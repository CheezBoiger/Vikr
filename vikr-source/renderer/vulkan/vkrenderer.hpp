//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_VULKAN_RENDERER_HPP
#define __VIKR_VULKAN_RENDERER_HPP


#include <renderer/renderer.hpp>
#include <resources/vulkan/vk_deallocator.hpp>


namespace vikr {


/**
  Vulkan Renderer, still in development, need to 
  set multiple layers after the full implementation of OpenGL.
*/
class VkRenderer : public Renderer {
public:

  vint32 Init() override;

  vvoid Render() override;


protected:

  vvoid CreateInstance();

private:
  /**
    Deallocator
  */
  VkDeallocator<VkInstance> instance {vkDestroyInstance};
};
} // vikr
#endif // __VIKR_VULKAN_RENDERER_HPP