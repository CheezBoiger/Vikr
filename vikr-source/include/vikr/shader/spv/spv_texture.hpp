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
  VkFormat GetNativeFormat(ImageFormat format);

  static struct {
    VkImage image;
    VkDeviceMemory memory;
  } StagingImage;

  SpvTexture() 
    : Texture(vikr_API_VULKAN)
  { }

  TextureTarget GetTargetFormat() override;
  ImageFormat GetFormat() override;
  TextureFilterMode GetFilterMin() override;
  TextureFilterMode GetFilterMax() override;
  
  TextureWrapMode GetWrapS() override;
  TextureWrapMode GetWrapT() override;
  TextureWrapMode GetWrapR() override;
  
  vbool IsMipmapping() override;
  vint32 GetWidth() override { return m_width; }
  virtual vint32 GetHeight() override = 0;
  virtual vint32 GetDepth() override = 0;

  std::string GetPath() override;
  std::string GetName() override;
  
  virtual vint32 Finalize() override = 0;

  vvoid SetFormat(ImageFormat format) override;
  vvoid SetFilterMin(TextureFilterMode filter) override;
  vvoid SetFilterMax(TextureFilterMode filter) override;
  vvoid SetTarget(TextureTarget target) override;
  vvoid SetWrapS(TextureWrapMode mode) override;
  vvoid SetWrapT(TextureWrapMode mode) override;
  vvoid SetWrapR(TextureWrapMode mode) override;
  
  vbool IsMultisampled() override;
  vvoid SetMultisampled(vbool enable) override;
  vvoid SetPath(std::string path) override;
  vvoid SetWidth(vint32 width) override;
  vvoid SetHeight(vint32 height) override;
  vvoid SetDepth(vint32 depth) override;
  vvoid SetSamples(vint32 samples) override;
  vint32 GetSamples() override;
  vvoid Cleanup() override;
  

protected:
  std::string m_path;
  std::string m_name;
  VkSampler m_sampler;
  VkImage m_image;
  VkDeviceMemory m_imageMemory;
  VkImageView m_imageview;

  VkFormat native_format;  
  vbool m_alpha;
  vint32 m_width                = 0;
};
} // vikr
#endif // __VIKR_SPV_TEXTURE_HPP