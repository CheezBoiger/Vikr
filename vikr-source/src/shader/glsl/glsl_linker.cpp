//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/glsl/glsl_linker.hpp>
#include <vikr/shader/glsl/glsl_compiler.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/util/vikr_log.hpp>

#include <array>

namespace vikr {


GLSLLinker::GLSLLinker()
{
}


vbool GLSLLinker::LoadShader(Shader *shader) {
  if (!shader) {
    return false;
  }

  if (shader->GetShaderLanguage() != vikr_GLSL) {
    return false;
  }

  if (shaders.find(shader->GetShaderStage()) == shaders.end()) {
    shaders[shader->GetShaderStage()] = shader;
  } else {
    return false;
  }

  return true;
}


vbool GLSLLinker::RemoveShader(ShaderStage stage) {
  std::map<ShaderStage, Shader *>::iterator it = shaders.find(stage);
  if (it != shaders.end()) {
    shaders.erase(it);
    return true;
  }
  return false;
}


vint32 GLSLLinker::Link() {
  vint32 success;
  std::array<GLchar, 1024> log;
  // Create a program id.
  program_id = CreateProgram();
  // Check if any of the shaders where not compiled...
  for (std::map<ShaderStage, Shader *>::iterator it = shaders.begin();
        it != shaders.end(); ++it) {
    if (!it->second->IsCompiled()) {
      VikrLog::DisplayMessage(VIKR_ERROR, 
        "Program cannot be linked => " + it->second->GetName() + " as it is not compiled!");
      glDeleteProgram(program_id);
      program_id = -1;
      return -1;
    }
    AttachShader(program_id, static_cast<vuint32>(it->second->GetNativeId()));
  }
  // link the program to the attach shaders.
  LinkProgram(program_id);
  GetProgramiv(program_id, GL_LINK_STATUS, &success);
  if(!success) {
    GetProgramInfoLog(program_id, 1024, NULL, log.data());
    VikrLog::DisplayMessage(vikr::VIKR_ERROR, std::string(log.data()));
    glDeleteProgram(program_id);
    program_id = -1;
  } else {
    is_linked = true;
  }
  return 1;
}
} // vikr