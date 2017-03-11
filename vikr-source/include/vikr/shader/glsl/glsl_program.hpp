//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_PROGRAM_HPP
#define __VIKR_GLSL_PROGRAM_HPP


#include <vikr/shader/shader_program.hpp>
#include <vikr/graphics/graphics.hpp>
#include <map>


namespace vikr {


/// GLSL Shader Program object used for OpenGL implementation.
/// Note this program object holds the program id of the shaders
/// linked to it, along with the references to those shader objects.
/// 
/// Ensure you remove the shader from this Program object before cleaning up
/// and deleting it.
class GLSLShaderProgram : public ShaderProgram {
public:
  GLSLShaderProgram();

  /// Get the shader associated with the given stage.
  Shader *GetShader(ShaderStage stage) override;

  /// Load a shader into this GLSL program. If a shader with the
  /// given shader stage is already in this Program, you can optionally
  /// force an insertion, thereby replacing the shader that was here before with
  /// the shader you are trying to add. This will not delete the shader that was
  /// previously in this progam, only merely removes it.
  vbool LoadShader(Shader *shader, vbool force = false) override;

  /// Removes a shader from this program, which can be done manally. Programmer
  /// can specify the shader stage, to which the Shader will be removed.
  vbool RemoveShader(ShaderStage stage) override;

  /// Get the native id of this program. This is strictly for OpenGL use.
  GLuint GetNativeId() { return program_id; }

  /// Build this program up. This will perorm linking, NOT COMPILING, of the shaders.
  vbool Build() override;

  /// Check if the Program is linked to it's shaders.
  vbool IsLinked() override { return islinked; }

  /// Cleanup the program, this will not delete the shaders!
  vvoid Cleanup() override { glDeleteProgram(program_id); }

private:
  /// the program id associated with this GLSLProgram object.
  GLuint program_id;

  /// variable to check if this GLSLprogram is linked.
  vbool islinked = false;

  /// Weak shader references. Contains the information of 
  /// shaders linked to this program.
  std::map<ShaderStage, Shader*> shaders;
};
} // vikr
#endif // __VIKR_GLSL_PROGRAM_HPP