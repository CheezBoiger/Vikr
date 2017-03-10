//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/graphics/vk/vk_vertexbuffer.hpp>


namespace vikr {


std::array<VkVertexInputAttributeDescription, kNumVertexDescriptions> 
VKVertexbuffer::GetAttributeDescriptions()
{
  std::array<VkVertexInputAttributeDescription, kNumVertexDescriptions> descriptions;
  descriptions[0].binding = 0;
  descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
  descriptions[0].offset = 0;
  descriptions[0].location = 0;
  return descriptions;
}
} // vikr