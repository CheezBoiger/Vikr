//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/glsl/glsl_shader.hpp>
#include <vikr/shader/glsl/glsl_compiler.hpp>
#include <vikr/shader/glsl/glsl_linker.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vikr/util/vikr_log.hpp>

namespace vikr {


GLSLShader::GLSLShader(ShaderStage stage)
  : Shader(stage, vikr_GLSL)
{
}


vvoid GLSLShader::Compile(std::string path) {
  GLSLCompiler compiler(shader_stage, path);
  compiler.GetPreprocessor()->SetSourceDirectory(include_searchpath);
  compiler.Compile();
  if (compiler.IsCompiled()) {
    shader_id = compiler.GetShaderId();
    is_compiled = true;
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "Shaders unsuccessfully compiled!");
  }
}
} // vikr