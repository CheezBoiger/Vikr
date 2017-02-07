//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/shader/glsl/glsl_linker.hpp>

#include <vikr/shader/glsl/glsl_linker.hpp>

#include <vikr/util/vikr_log.hpp>


namespace vikr {


GLSLShaderProgram::GLSLShaderProgram()
  : program_id(0)
  , islinked(false)
{
}


vbool GLSLShaderProgram::LoadShader(Shader *shader, vbool force) {
  if (!shader) {
    return false;
  }
  std::map<ShaderStage, Shader *>::iterator it = 
    shaders.find(shader->GetShaderStage());
  vbool success = false;
  if (it != shaders.end() && force) {
    shaders[shader->GetShaderStage()] = shader;
    success = true;
  } else if (it == shaders.end()) {
    shaders[shader->GetShaderStage()] = shader;
    success = true;
  }
  return success;
}


vbool GLSLShaderProgram::RemoveShader(ShaderStage stage) {
  vbool success = false;
  std::map<ShaderStage, Shader *>::iterator it =
    shaders.find(stage);
  if (it != shaders.end()) {
    shaders.erase(it);
  }
  return success;
}


Shader *GLSLShaderProgram::GetShader(ShaderStage stage) {
  // this can be auto, but I enjoy writing out the data type.
  std::map<ShaderStage, Shader *>::iterator it = 
    shaders.find(stage);
  if (it == shaders.end()) {
    return nullptr;
  }
  return it->second;
}


vbool GLSLShaderProgram::Build() {
  vbool success = false;
  GLSLLinker linker;
  for (auto shader : shaders) {
    if (!shader.second->IsCompiled()) {
      VikrLog::DisplayMessage(VIKR_ERROR, "Shader => " 
        + shader.second->GetName() 
        + " was not compiled! Aborting Build.");
      return false;
    }
    linker.LoadShader(shader.second);
  }

  linker.Link();

  if (linker.IsLinked()) {
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "Linker has successfully linked!");
    program_id = linker.GetProgramId();
    success = true;
  }
  return success;
}
} // vikr