//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_SHADER_HPP
#define __VIKR_GLSL_SHADER_HPP

#include <shader/shader.hpp>

namespace vikr {


/**
  OpenGL GLSL Shader module.
*/
class GLSLShader : public Shader {
public:
  GLSLShader();

  vvoid Compile(std::string vs, std::string fs, std::string gs = "") override;
  vvoid Use() override { UseProgram(shader_id); }
  vvoid Cleanup() override { glDeleteProgram(shader_id); }

  vvoid SetValue(std::string name, vint32 value) override;
  vvoid SetValue(std::string name, vbool value)  override;
  vvoid SetValue(std::string name, vreal32 value) override;
  vvoid SetValue(std::string name, vreal64 value) override;
  vvoid SetValue(std::string name, glm::vec2 value) override;
  vvoid SetValue(std::string name, glm::vec3 value) override;
  vvoid SetValue(std::string name, glm::vec4 value) override;
  vvoid SetValue(std::string name, glm::mat2 value) override;
  vvoid SetValue(std::string name, glm::mat3 value) override;
  vvoid SetValue(std::string name, glm::mat4 value) override;
  
};
} // vikr
#endif // __VIKR_GLSL_SHADER_HPP