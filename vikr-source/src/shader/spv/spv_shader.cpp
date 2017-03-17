//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/spv/spv_shader.hpp>
#include <vikr/shader/spv/spv_compiler.hpp>
#include <vikr/graphics/vk/vk_device.hpp>

#include <vikr/util/vikr_log.hpp>


namespace vikr {


SpvShader::SpvShader(ShaderStage stage)
  : Shader(vikr_API_VULKAN, stage, vikr_SPIRV)
{
}


vvoid SpvShader::Compile(std::string path) {
  if (path.empty()) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Can not Compile empty path!");
    return;
  }
  
  {
    SpvCompiler compiler(device, shader_stage, path);
    compiler.GetPreprocessor()->SetSourceDirectory(include_searchpath);
    compiler.Compile();

    if (compiler.IsCompiled()) {
      module = compiler.GetShaderModule();
      pipelineShaderStageInfo = compiler.GetPipelineShaderStageInfo();
      VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "Successful SPIR-V Shader Compiler");
      // No need to cleanup the compiler, since all resources are moving to this shader.
    } else {
      VikrLog::DisplayMessage(VIKR_ERROR, "Unsuccessful SPIR-V Shader Compilation!");
      compiler.Cleanup();
    }
  }
}


vvoid SpvShader::Cleanup()
{
  vkDestroyShaderModule(
    static_cast<VKRenderDevice *>(GetRenderDevice())->GetLogicalDevice(), 
    module, 
    nullptr
  );
}
} // vikr