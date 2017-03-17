//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/spv/spv_texture_2d.hpp>
#include <vikr/graphics/vk/vk_device.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {



vint32 SpvTexture2D::Finalize()
{
  vint32 c;
  vbyte *bytecode = Texture::CreateImageByteCode(m_path, &m_width, &m_height, &c, m_alpha);
  VKRenderDevice *device = static_cast<VKRenderDevice *>(GetRenderDevice());
  VkImageCreateInfo imageCreateInfo = { };
  imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
  imageCreateInfo.extent.width = m_width;
  imageCreateInfo.extent.height = m_height;
  imageCreateInfo.extent.depth = 1;
  imageCreateInfo.mipLevels = 1;
  imageCreateInfo.arrayLayers = 1;
  imageCreateInfo.format = native_format;
  imageCreateInfo.tiling = VK_IMAGE_TILING_LINEAR;
  imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
  imageCreateInfo.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT;  
  imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageCreateInfo.flags = 0;

  // Stage the image first.
  VkResult result = vkCreateImage(device->GetLogicalDevice(), &imageCreateInfo, nullptr,
    &StagingImage.image);
  if (result != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, R"(Failed to stage the image in
      SPV texture 2D !!!
    )");
  }

  VkMemoryRequirements memReqs;
  vkGetImageMemoryRequirements(device->GetLogicalDevice(), StagingImage.image, &memReqs); 
  VkMemoryAllocateInfo allocationInfo = { };
  allocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocationInfo.pNext = nullptr;
  allocationInfo.memoryTypeIndex = device->FindMemorytype(memReqs.memoryTypeBits, 
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
  
  result = vkAllocateMemory(device->GetLogicalDevice(), &allocationInfo, nullptr, 
    &StagingImage.memory);

  vkBindImageMemory(device->GetLogicalDevice(), StagingImage.image, StagingImage.memory, 0);
  // still working on it... Need to transfer from staging buffer to the image view itself.

  Texture::FreeImageByteCode(bytecode);
  return 1;
}
} // vikr