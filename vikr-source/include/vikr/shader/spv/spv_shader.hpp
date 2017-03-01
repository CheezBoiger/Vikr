//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPV_SHADER_HPP
#define __VIKR_SPV_SHADER_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/shader/shader.hpp>

#include <vikr/resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


class VKDevice;


class SpvShader : public Shader {
public:
 SpvShader(VKDevice *device, ShaderStage stage);
  
  vvoid Compile(std::string path) override;
  vvoid Cleanup() override;

  VkShaderModule GetNativeId() { return module.Get(); }
  
private:
  /**
    Shader module for vulkan.
  */
  VkMemoryManager<VkShaderModule> module;

  /**
    Weak ref.
  */
  VKDevice *device = nullptr;
};
} // vikr
#endif // __VIKR_SPV_SHADER_HPP