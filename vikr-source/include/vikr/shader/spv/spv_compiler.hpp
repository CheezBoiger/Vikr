//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPIRV_COMPILER_HPP
#define __VIKR_SPIRV_COMPILER_HPP


#include <vikr/shader/shader.hpp>
#include <vikr/shader/shader_config.hpp>
#include <vikr/shader/glsl/glsl_preprocessor.hpp>

//
// We write SPIR-V shader here!
//

namespace vikr {


class VKRenderDevice;

/**
  SpirV Compiler
*/
class SpvCompiler {
public:
  SpvCompiler(VKRenderDevice *device, ShaderStage stage, std::string filepath);

  vvoid Compile();

  vvoid Cleanup();

  vbool IsCompiled() { return compiled; }

  ShaderStage GetshaderStage() { return shader_stage; }

  std::string GetFilepath() { return filepath; }
  vvoid SetFilePath(std::string path) { filepath = path; }

  GLSLPreprocessor *GetPreprocessor() { return &preprocessor; }

  VkShaderModule GetShaderModule() { return shaderModule; }
  VkPipelineShaderStageCreateInfo GetPipelineShaderStageInfo() { return pipelineShaderStage; }
  
private:

  vvoid LoadShaderFile();
  
  VkShaderModule shaderModule;
  VkPipelineShaderStageCreateInfo pipelineShaderStage;
  vbool compiled;

  std::string filepath;

  ShaderStage shader_stage;

  GLSLPreprocessor preprocessor;
  
  // weak ref.
  VKRenderDevice *device = nullptr;
};
} // vikr
#endif // __VIKR_SPIRV_COMPILER_HP