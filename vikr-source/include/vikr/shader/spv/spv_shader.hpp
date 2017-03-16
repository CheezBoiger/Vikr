//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPV_SHADER_HPP
#define __VIKR_SPV_SHADER_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/shader/shader.hpp>

#include <vikr/graphics/graphics.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


class VKRenderDevice;


class SpvShader : public Shader {
public:
 SpvShader(ShaderStage stage);
  
  vvoid Compile(std::string path) override;
  vvoid Cleanup() override;

  VkShaderModule GetShaderModule() { return module; }
  
private:
  /// Shader module for vulkan.
  VkShaderModule module;

  /// Information of the shader module for pipelines.
  VkPipelineShaderStageCreateInfo pipelineShaderStageInfo;

  /// Weak ref.
  VKRenderDevice *device = nullptr;
};
} // vikr
#endif // __VIKR_SPV_SHADER_HPP