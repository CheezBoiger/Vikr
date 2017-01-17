//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_SHADER_HPP
#define __VIKR_GLSL_SHADER_HPP

#include <vikr/shader/shader.hpp>

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

};
} // vikr
#endif // __VIKR_GLSL_SHADER_HPP