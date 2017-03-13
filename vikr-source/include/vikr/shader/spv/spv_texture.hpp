//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPV_TEXTURE_HPP
#define __VIKR_SPV_TEXTURE_HPP


#include <vikr/shader/texture.hpp>
#include <vikr/graphics/vk/vk.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>

#include <vector>


namespace vikr {


class VKRenderDevice;


/// SpvTexture contains values that vulkan describes for 
/// Showing images on screen. Samplers are used to access
/// texture data.
class SpvTexture : public Texture {
public:
  SpvTexture(VKRenderDevice *device);


private:

  VkMemoryManager<VkSampler> sampler;
  VkMemoryManager<VkImage> image;
  VkMemoryManager<VkImageView> imageview;

  VKRenderDevice *device;  
};
} // vikr
#endif // __VIKR_SPV_TEXTURE_HPP