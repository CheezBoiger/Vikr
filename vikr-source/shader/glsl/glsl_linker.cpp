//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/glsl_linker.hpp>
#include <shader/glsl/glsl_compiler.hpp>
#include <shader/shader.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


GLSLLinker::GLSLLinker(Shader *shader)
  : ShaderLinker(shader)
{
}


vint32 GLSLLinker::Link(IShaderCompiler *vs, IShaderCompiler *fs, IShaderCompiler *gs) {
  GLSLCompiler *vs_compiler = nullptr;
  GLSLCompiler *fs_compiler = nullptr;
  GLSLCompiler *gs_compiler = nullptr;
  if (vs->GetShaderType() == vikr_GLSL) {
    vs_compiler = ToCompiler(vs);
  }
  if (fs->GetShaderType() == vikr_GLSL) {
    fs_compiler = ToCompiler(fs);
  }
  if (gs != nullptr && gs->GetShaderType() == vikr_GLSL) {
    gs_compiler = ToCompiler(gs);
  }
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
  AttachShader(shader_ref->GetProgram(), vs->GetShaderId());
  AttachShader(shader_ref->GetProgram(), fs->GetShaderId());
  LinkProgram(shader_ref->GetProgram());
  GetProgramiv(shader_ref->GetProgram(), GL_LINK_STATUS, &success);
  if(!success) {
    GetProgramInfoLog(shader_ref->GetProgram(), 1024, NULL, log);
    VikrLog::DisplayMessage(vikr::VIKR_ERROR, std::string(log));
    return -1;
  }
  vs->Cleanup();
  fs->Cleanup();
  if(gs != nullptr) {
    gs->Cleanup();
  }
  return 1;
}


GLSLCompiler *GLSLLinker::ToCompiler(IShaderCompiler *compiler) {
  return static_cast<GLSLCompiler *>(compiler);
}
} // vikr