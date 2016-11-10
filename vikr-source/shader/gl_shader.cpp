#include <shader/gl_shader.hpp>
#include <util/vikr_filesystem.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

namespace vikr {


GLShader::GLShader(VikrPipelineStage stage, std::string filepath) 
  : pipeline_stage(stage)
  , compiled(false) {
  LoadShaderFile(filepath);
}


vvoid GLShader::LoadShaderFile(std::string filepath) {
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
  const GLchar* shader_code_c = shader_code.c_str();
  shader_id = glCreateShader(GL_VERTEX_SHADER);
  ShaderSource(shader_id, 1, &shader_code_c, NULL);
}


vvoid GLShader::Compile() {
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


Shader::Shader()
  : program(CreateProgram()) 
{
  
}


vvoid Shader::Link(GLShader* vs, GLShader* fs, GLShader* gs) {
  vint32 success;
  GLchar log[1024];
  if (!vs->IsCompiled()) {
    vs->Compile();
  }
  if (!fs->IsCompiled()) {
    fs->Compile();
  }

  if (gs != nullptr && !gs->IsCompiled()) {
    gs->Compile();
  }
  glAttachShader(program, vs->GetShaderId());
  glAttachShader(program, fs->GetShaderId());
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 1024, NULL, log);
    std::cout << log << std::endl;
  }
  vs->Cleanup();
  fs->Cleanup();

  if (gs != nullptr) {
    gs->Cleanup();
  }
}
} // vikr