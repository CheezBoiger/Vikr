//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_LINKER_HPP
#define __VIKR_GLSL_LINKER_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <vikr/graphics/graphics.hpp>
#include <vikr/shader/shader_config.hpp>


#include <map>


namespace vikr {


class GLSLCompiler;
class Shader;




/// Linker produces a program id from the linked shaders.
class GLSLLinker {
public:
  GLSLLinker();

  
  /// Links the loaded shaders into a program for OpenGL use. Returns 
  /// true (1) if successful link. False is returned otherwise (or 0).
  vint32 Link();

  /// Load a shader temorarily into the Linker. Shaders loaded 
  /// are used as references to link a program with. Returns true if 
  /// a shader was successfully loaded. False is returned if the shader
  /// fails to load. This is due as to whether there is already a shader 
  /// with the same shader stage loaded. 
  vbool LoadShader(Shader *shader);

  /// Removes a shader from the linkers references. Typically, there is only
  /// one shader per shader stage, so you may remove the Shader reference based on 
  /// the stage you wish to give. True is returned if a shader was successfully removed,
  /// false if linker fails to remove a shader, this is only if there is no shader with the
  /// given shader stage available.
  vbool RemoveShader(ShaderStage stage);

  /// Check if the linker has already linked.
  vbool IsLinked() { return is_linked; }

  
  /// Get the Output program id. Returns the program id if the linker 
  /// has linked successfully, otherwise -1 returns if linker did not
  /// link successfully, or yet.
  GLuint GetProgramId() { return program_id; }

private:
  /// Map of weak shader references to be linked together.
  std::map<ShaderStage, Shader *> shaders;  

  /// The output program id.
  GLuint program_id = 0;

  
  /// Check if the linker has linked.
  vbool is_linked = false;
};
} // vikr
#endif // __VIKR_GLSL_LINKER_HPP
