//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/glsl_linker.hpp>
#include <shader/glsl/glsl_compiler.hpp>
#include <shader/shader.hpp>
#include <util/vikr_log.hpp>

#include <array>

namespace vikr {


GLSLLinker::GLSLLinker(Shader *shader)
  : shader(shader)
{
}


vint32 GLSLLinker::Link(GLSLCompiler *vs, GLSLCompiler *fs, GLSLCompiler *gs) {
  vint32 success;
  std::array<GLchar, 1024> log;
  if(!vs->IsCompiled() || !fs->IsCompiled()) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Linker can not link uncompiled shaders!");
    return 0;
  }
  if(gs && !gs->IsCompiled()) {
    gs->Compile();
  }
  AttachShader(shader->GetProgramId(), vs->GetShaderId());
  AttachShader(shader->GetProgramId(), fs->GetShaderId());
  if (gs->IsCompiled()) {
    AttachShader(shader->GetProgramId(), gs->GetShaderId());
  }
  LinkProgram(shader->GetProgramId());
  GetProgramiv(shader->GetProgramId(), GL_LINK_STATUS, &success);
  if(!success) {
    GetProgramInfoLog(shader->GetProgramId(), 1024, NULL, log.data());
    VikrLog::DisplayMessage(vikr::VIKR_ERROR, std::string(log.data()));
  }
  vs->Cleanup();
  fs->Cleanup();
  if(gs != nullptr) {
    gs->Cleanup();
  }
  if (success) {
    is_linked = true;
  }
  return 1;
}
} // vikr