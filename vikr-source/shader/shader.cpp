#include <shader/shader.hpp>
#include <shader/gl_shader.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


Shader::Shader()
  : program(CreateProgram())
{

}


vvoid Shader::Link(IShader* vs, IShader* fs, IShader* gs) {
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
  AttachShader(program, vs->GetShaderId());
  AttachShader(program, fs->GetShaderId());
  LinkProgram(program);
  GetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success) {
    GetProgramInfoLog(program, 1024, NULL, log);
    VikrLog::DisplayMessage(vikr::VIKR_ERROR, std::string(log));
  }
  vs->Cleanup();
  fs->Cleanup();

  if(gs != nullptr) {
    gs->Cleanup();
  }
}
} // vikr