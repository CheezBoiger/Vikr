//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/glsl_linker.hpp>
#include <shader/glsl/glsl_compiler.hpp>
#include <shader/shader.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


GLSLLinker::GLSLLinker(Shader *shader)
  : shader(shader)
{
}


vint32 GLSLLinker::Link(GLSLCompiler *vs, GLSLCompiler *fs, GLSLCompiler *gs) {
  GLSLCompiler *vs_compiler = nullptr;
  GLSLCompiler *fs_compiler = nullptr;
  GLSLCompiler *gs_compiler = nullptr;
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
  AttachShader(shader->GetShaderId(), vs->GetShaderId());
  AttachShader(shader->GetShaderId(), fs->GetShaderId());
  LinkProgram(shader->GetShaderId());
  GetProgramiv(shader->GetShaderId(), GL_LINK_STATUS, &success);
  if(!success) {
    GetProgramInfoLog(shader->GetShaderId(), 1024, NULL, log);
    VikrLog::DisplayMessage(vikr::VIKR_ERROR, std::string(log));
    return -1;
  }
  vs->Cleanup();
  fs->Cleanup();
  if(gs != nullptr) {
    gs->Cleanup();
  }
  is_linked = true;
  return 1;
}
} // vikr