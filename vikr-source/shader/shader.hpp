//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SHADER_HPP
#define __VIKR_SHADER_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <glm/glm.hpp>
#include <string>

namespace vikr {

enum ShaderType {
  vikr_GLSL,
  vikr_SPIRV
};


/**
  For now it only works with OpenGL, Spir-V not yet implemented!
*/
class Shader {
public:
  Shader();
  Shader(Shader&& shader) = default;
  Shader& operator=(Shader&& shader) = default;
  virtual ~Shader() { }

  virtual vvoid Compile(std::string vs, std::string fs, std::string gs = "") = 0;
  virtual vvoid Use() = 0;
  virtual vvoid Cleanup() = 0;
  vuint32 GetShaderId() { return shader_id; }
  vbool IsLinked() { return is_linked; }

  virtual vvoid SetValue(std::string name, vint32 value) = 0;
  virtual vvoid SetValue(std::string name, vbool value) = 0;
  virtual vvoid SetValue(std::string name, vreal32 value) = 0;
  virtual vvoid SetValue(std::string name, vreal64 value) = 0;
  virtual vvoid SetValue(std::string name, glm::vec2 value) = 0;
  virtual vvoid SetValue(std::string name, glm::vec3 value) = 0;
  virtual vvoid SetValue(std::string name, glm::vec4 value) = 0;
  virtual vvoid SetValue(std::string name, glm::mat2 value) = 0;
  virtual vvoid SetValue(std::string name, glm::mat3 value) = 0;
  virtual vvoid SetValue(std::string name, glm::mat4 value) = 0;


  ShaderType GetShaderType() { return shader_type; }

protected:

  ShaderType shader_type;

  vuint32 shader_id;
  vbool is_linked;
  VIKR_DISALLOW_COPY_AND_ASSIGN(Shader);
};
} // vikr
#endif // __VIKR_SHADER_HPP