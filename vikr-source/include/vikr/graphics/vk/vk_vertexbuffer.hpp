//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_VERTEXBUFFER_HPP
#define __VIKR_VK_VERTEXBUFFER_HPP


#include <vikr/graphics/vertexbuffer.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>

namespace vikr {


class VkVertexbuffer : public Vertexbuffer {
public:

  vuint64 GetVertexBufferId() override {
    return id;
  }

  /**
    Store the VkBuffer id into this VertexBuffer object. 
    WARNING (test) : Simply testing if this will work as VkBuffer is just a uint64_t id.
  */
  vvoid StoreVertexBufferId(vuint64 vbo) override {
    m_vbo.Replace(); 
    m_vbo = vbo;
  }

  vuint64 GetElementBufferId() override;
  vvoid StoreElementBufferId(vuint64 ibo) override;

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