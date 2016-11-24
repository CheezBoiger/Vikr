//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/glsl_compiler.hpp>
#include <util/vikr_filesystem.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

namespace vikr {


GLSLCompiler::GLSLCompiler(VikrGLPipelineStage stage, std::string filepath) 
  : pipeline_stage(stage)
  , compiled(false) {
  LoadShaderFile(filepath);
}


vvoid GLSLCompiler::LoadShaderFile(std::string filepath) {
  // This needs to go into filesystem insteam.
  std::string shader_code;
  std::ifstream shader_file;
  shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    shader_file.open(filepath);
    std::stringstream shaderstream;
    shaderstream << shader_file.rdbuf();
    shader_file.close();
    shader_code = shaderstream.str();
  } catch (std::ifstream::failure e) {
    // must debug...
  }
  // We can preprocess here!
  const GLchar* shader_code_c = shader_code.c_str();
  shader_id = CreateShader(pipeline_stage);
  ShaderSource(shader_id, 1, &shader_code_c, NULL);
}


vvoid GLSLCompiler::Compile() {
  vint32 success;
  GLchar log[1024];
  CompileShader(shader_id);
  GetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    GetShaderInfoLog(shader_id, 1024, NULL, log);
    std::cout << log << std::endl;
  } else {
    compiled = true;
  }
}
} // vikr