//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/graphics/vk/vk_vertexbuffer.hpp>


namespace vikr {


VkVertexInputBindingDescription VKVertexbuffer::GetBindingDescription() 
{
  VkVertexInputBindingDescription binding_description;
  binding_description.binding = 0;
  // Set No stride, as our vertices will be packed as a batch. 
  binding_description.stride = sizeof(Vertex);
  binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  return binding_description;
}


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