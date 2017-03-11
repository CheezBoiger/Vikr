//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_SHADER_HPP
#define __VIKR_GLSL_SHADER_HPP

#include <vikr/shader/shader.hpp>

#include <vikr/graphics/graphics.hpp>


namespace vikr {


/**
  OpenGL GLSL Shader module.
*/
class GLSLShader : public Shader {
public:
  GLSLShader(ShaderStage stage);

  vvoid Compile(std::string path) override;
  vvoid Cleanup() override { glDeleteShader(shader_id); }

  GLuint GetNativeId() { return shader_id; }
  
private:

  GLuint shader_id;

};
} // vikr
#endif // __VIKR_GLSL_SHADER_HPP