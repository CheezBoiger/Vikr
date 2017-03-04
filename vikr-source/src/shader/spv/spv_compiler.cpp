//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/spv/spv_compiler.hpp>

#include <vikr/util/vikr_log.hpp>
#include <vikr/shader/glsl/glsl_preprocessor.hpp>
#include <vikr/graphics/vk/vk_device.hpp>


namespace vikr {


const char *std_entry_point = "main";


SpvCompiler::SpvCompiler(VKRenderDevice *device, ShaderStage stage, std::string filepath)
  : filepath(filepath)
  , device(device)
  , shader_stage(stage)
  , compiled(false)
  , shaderModule(0)
{
}


vvoid SpvCompiler::Compile() {
  if (filepath.empty()) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Spir-V could not compile this shader module!"); 
    return;
  }
  LoadShaderFile();
}


vvoid SpvCompiler::LoadShaderFile() {
  std::string shader_code = preprocessor.Preprocess(filepath);
  VkShaderModuleCreateInfo information;
  information.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  information.codeSize = shader_code.size();
  information.pCode = (vuint32 *)shader_code.c_str();
  if (vkCreateShaderModule(device->GetVkDevice(), &information, nullptr, &shaderModule) != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failure to create SPV shader module => " + filepath);
    return;
  }
  switch (shader_stage) {
    case vikr_VERTEX_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
      break;
    case vikr_FRAGMENT_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
      break;
    case vikr_TESS_CONTROL_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
      break;
    case vikr_TESS_EVALUATION_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
      break;
    case vikr_GEOMETRY_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
      break;
    case vikr_COMPUTE_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
      break;
    default: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
      break;
  }
  pipelineShaderStage.module = shaderModule;
  pipelineShaderStage.pName = std_entry_point;
  
}
} // vikr