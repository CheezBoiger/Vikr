//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/glsl/glsl_compiler.hpp>
#include <vikr/util/vikr_filesystem.hpp>
#include <vikr/util/vikr_log.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <array>

namespace vikr {


GLSLCompiler::GLSLCompiler(VikrGLPipelineStage stage, std::string filepath) 
  : pipeline_stage(stage)
  , compiled(false) 
  , filepath(filepath)
{
}


vvoid GLSLCompiler::LoadShaderFile() {
  // This needs to go into filesystem insteam.
  std::string shader_code = preprocessor.Preprocess(filepath);
  const GLchar* shader_code_c = shader_code.c_str();
  shader_id = CreateShader(pipeline_stage);
  ShaderSource(shader_id, 1, &shader_code_c, NULL);
}


vvoid GLSLCompiler::Compile() {
  LoadShaderFile();
  vint32 success = false;
  std::array<GLchar, 1024> log;
  if (!filepath.empty()) {
    CompileShader(shader_id);
    GetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success) {
      GetShaderInfoLog(shader_id, log.size(), NULL, log.data());
      VikrLog::DisplayMessage(VIKR_ERROR, std::string(log.data()));
    } else {
      compiled = true;
    }
  }
}
} // vikr