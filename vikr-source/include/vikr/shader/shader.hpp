//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SHADER_HPP
#define __VIKR_SHADER_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <vikr/shader/shader_config.hpp>
#include <vikr/scene/guid_generator.hpp>

#include <glm/glm.hpp>
#include <string>

namespace vikr {



/// For now it only works with OpenGL, Spir-V not yet implemented!
class Shader : public GUID {
protected:
  /// Must not be instantiated by the user.
  Shader(ShaderStage stage = vikr_VERTEX_SHADER, ShaderLanguage lang = vikr_NOLANG);

public:
  static const vuint32 kNoShaderId;
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Shader);
  virtual ~Shader() { }

  /// Compile the Shader for the Program to use.
  virtual vvoid Compile(std::string path) = 0;

  /// Set the include search path for the file. This is for macro use of the #include.
  vvoid IncludeSearchPath(std::string path) { include_searchpath = path; }

  /// Clean up the shader.
  virtual vvoid Cleanup() = 0;

  
  /// Get the Shader language.
  ShaderLanguage GetShaderLanguage() { return shader_lang; }

  ShaderStage GetShaderStage() { return shader_stage; }

  /// Sets the name of the shader.
  vvoid SetName(std::string name) { shader_name = name; }

  /// Grab the name of the shader.
  std::string GetName() { return shader_name; }

  /// Check if the shader is compiled.
  vbool IsCompiled() { return is_compiled; }

protected:
  /// Shader stage of this shader object.
  ShaderStage shader_stage              = vikr_VERTEX_SHADER;

  /// Shader Language.
  ShaderLanguage shader_lang            = vikr_NOLANG;

  /// The search path to use for including.
  std::string include_searchpath        = ".";

  /// The shader name.
  std::string shader_name               = "noname";

  vbool is_compiled                     = false;
  VIKR_DISALLOW_COPY_AND_ASSIGN(Shader);
};
} // vikr
#endif // __VIKR_SHADER_HPP