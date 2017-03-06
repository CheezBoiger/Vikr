//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_PROGRAM_HPP
#define __VIKR_GLSL_PROGRAM_HPP


#include <vikr/shader/shader_program.hpp>
#include <vikr/graphics/graphics.hpp>
#include <map>


namespace vikr {


class GLSLShaderProgram : public ShaderProgram {
public:
  GLSLShaderProgram();

  
  Shader *GetShader(ShaderStage stage) override;
  vbool LoadShader(Shader *shader, vbool force = false) override;
  vbool RemoveShader(ShaderStage stage) override;
  vuint32 GetNativeId() { return program_id; }

  vbool Build() override;
  vbool IsLinked() override { return islinked; }

  vvoid Cleanup() override { glDeleteProgram(program_id); }

private:

  vuint32 program_id;
  vbool islinked = false;

  /**
    Weak shader references.
  */
  std::map<ShaderStage, Shader*> shaders;
};
} // vikr
#endif // __VIKR_GLSL_PROGRAM_HPP