//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_UNIFORMBUFFER_HPP
#define __VIKR_VK_UNIFORMBUFFER_HPP


#include <vikr/graphics/uniformbuffer.hpp>
#include <vikr/graphics/vk/vk_device.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>
#include <vikr/graphics/graphics.hpp>


namespace vikr {


/// Vulkan Uniformbuffer, designed for the very best of information...
/// well, not really. But it was specifically designed to adhere to 
/// number data, rather than textures or samplers.
///
/// Still a work in progress...
class VKUniformbuffer : public Uniformbuffer {
public:
  VKUniformbuffer() 
    : Uniformbuffer(vikr_API_VULKAN)
  { }

  vvoid Generate(vuint32 bind, vuint32 bytes) override;
  vvoid Reallocate(vuint32 new_bytes) override;
  vvoid Update() override;
  vvoid StoreData(vuint32 offset, vuint32 bytes, vbyte *data) override;
  vvoid Cleanup() override;

  vvoid SetInt(vuint32 offset, vint32 value) override;
  vvoid SetBool(vuint32 offset, vbool value) override;
  vvoid SetVector4fv(vuint32 offset, glm::vec4 value) override;
  vvoid SetVector3fv(vuint32 offset, glm::vec3 value) override;
  vvoid SetVector2fv(vuint32 offset, glm::vec2 value) override;
  vvoid SetFloat(vuint32 offset, vreal32 value) override;
  vvoid SetDouble(vuint32 offset, vreal64 value) override;
  vvoid SetMat4(vuint32 offset, glm::mat4 value) override;
  vvoid SetMat3(vuint32 offset, glm::mat3 value) override;
  vvoid SetMat2(vuint32 offset, glm::mat2 value) override;

private:
  VkBuffer stagingBuffer;
  VkBuffer uniformBuffer;
  VkDeviceMemory stagingMemory;
  VkDeviceMemory uniformMemory;
};
} // vikr
#endif // __VIKR_VK_UNIFORMBUFFER_HPP 