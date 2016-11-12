#include <shader/shader.hpp>
#include <shader/gl_shader.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


Shader::Shader()
  : program(CreateProgram())
{

}


vvoid Shader::Link(GLShader* vs, GLShader* fs, GLShader* gs) {
  vint32 success;
  GLchar log[1024];
  if(!vs->IsCompiled()) {
    vs->Compile();
  }
  if(!fs->IsCompiled()) {
    fs->Compile();
  }

  if(gs != nullptr && !gs->IsCompiled()) {
    gs->Compile();
  }
  glAttachShader(program, vs->GetShaderId());
  glAttachShader(program, fs->GetShaderId());
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(program, 1024, NULL, log);
    VikrLog::DisplayMessage(vikr::VIKR_ERROR, std::string(log));
  }
  vs->Cleanup();
  fs->Cleanup();

  if(gs != nullptr) {
    gs->Cleanup();
  }
}
} // vikr