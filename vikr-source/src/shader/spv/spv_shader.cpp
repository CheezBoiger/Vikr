//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/spv/spv_shader.hpp>
#include <vikr/shader/spv/spv_compiler.hpp>
#include <vikr/graphics/vk/vk_device.hpp>

#include <vikr/util/vikr_log.hpp>


namespace vikr {


SpvShader::SpvShader(VKRenderDevice *device, ShaderStage stage)
  : device(device)
  , Shader(stage, vikr_SPIRV)
{
}


vvoid SpvShader::Compile(std::string path) {
  if (path.empty()) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Can not Compile empty path!");
    return;
  }
  SpvCompiler compiler(device, shader_stage, path);
  compiler.GetPreprocessor()->SetSourceDirectory(include_searchpath);
  compiler.Compile();

  if (compiler.IsCompiled()) {
     
  } else {
  }
}
} // vikr