//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_VERTEXBUFFER_HPP
#define __VIKR_VK_VERTEXBUFFER_HPP


#include <vikr/graphics/vertexbuffer.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>

#include <vikr/graphics/graphics.hpp>

namespace vikr {


class VKVertexbuffer : public Vertexbuffer {
public:

  vvoid BufferSubData(vint32 offset, vuint32 size, vvoid *data) override;

  vvoid Cleanup() override {
    m_vbo.Replace();
    id = -1;
  }

  vvoid StoreVkBuffer(VkBuffer &buf);

  
  /**
    Get the Binding Description.
  */
  static VkVertexInputBindingDescription GetBindingDescription() {
    VkVertexInputBindingDescription binding_description;
    binding_description.binding = 0;
    // Set No stride, as our vertices will be packed as a batch. 
    binding_description.stride = 0; 
    binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  }

private:

  /**
    Essentually a VkBuffer id.
  */
  vuint64 id;

  /**
    vbo buffer.
  */ 
  VkMemoryManager<VkBuffer> m_vbo;
 
};
} // vikr
#endif // __VIKR_VK_VERTEXBUFFER_HPP