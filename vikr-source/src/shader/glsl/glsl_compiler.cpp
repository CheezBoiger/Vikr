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


GLSLCompiler::GLSLCompiler(ShaderStage stage, std::string filepath) 
  : compiled(false) 
  , filepath(filepath)
  , shader_stage(stage)
{
}


vvoid GLSLCompiler::LoadShaderFile() {
  // This needs to go into filesystem insteam.
  std::string shader_code = preprocessor.Preprocess(filepath);
  const GLchar* shader_code_c = shader_code.c_str();
  GLenum s = GL_VERTEX_SHADER;
  switch (shader_stage) {
    case VERTEX_SHADER: s = GL_VERTEX_SHADER; break;
    case FRAGMENT_SHADER: s = GL_FRAGMENT_SHADER; break;
    case GEOMETRY_SHADER: s = GL_GEOMETRY_SHADER; break;
    case COMPUTE_SHADER: s = GL_COMPUTE_SHADER; break;
    case TESS_CONTROL_SHADER: s = GL_TESS_CONTROL_SHADER; break;
    case TESS_EVALUATION_SHADER: s = GL_TESS_EVALUATION_SHADER; break;
    default: s = GL_VERTEX_SHADER; break;
  }
  shader_id = CreateShader(s);
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
      Cleanup();
      compiled = false;
    } else {
      compiled = true;
    }
  }
}
} // vikr