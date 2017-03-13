//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_VERTEXBUFFER_HPP
#define __VIKR_VK_VERTEXBUFFER_HPP


#include <vikr/graphics/vertexbuffer.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>
#include <vikr/mesh/vertex.hpp>
#include <array>
#include <vikr/graphics/graphics.hpp>

namespace vikr {


const vuint32 kNumVertexDescriptions = 6;
class VKRenderDevice;


/// Vulkan specific vertex buffer for Vulkan rendering.
class VKVertexbuffer : public Vertexbuffer {
public:
  VKVertexbuffer(VKRenderDevice *device);

  /// Subdata buffering.
  vvoid BufferData(VertexUsageType type, vuint32 size, Vertex *data) override;

  /// Cleanup this Vkbuffer object.
  vvoid Cleanup() override {
    m_vbo.Replace();  
  }

  /// Store the vk buffer.
  vvoid StoreVkBuffer(VkBuffer &buf);

  /// Get the Binding Description.
  static VkVertexInputBindingDescription GetBindingDescription();

  /// Get Attribute descrptions, or the descriptions associated with vertex input
  /// buffers.
  static std::array<VkVertexInputAttributeDescription, kNumVertexDescriptions> GetAttributeDescriptions();

private:
  //
  //  vbo buffer.
  VkMemoryManager<VkBuffer> m_vbo;
 
  
  VKRenderDevice *device;
};
} // vikr
#endif // __VIKR_VK_VERTEXBUFFER_HPP