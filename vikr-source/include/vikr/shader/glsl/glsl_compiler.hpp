//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLSL_COMPILER_H
#define __VIKR_GLSL_COMPILER_H

#include <vikr/shader/shader.hpp>
#include <vikr/shader/glsl/glsl_preprocessor.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <string>


namespace vikr {

/**
  GLSL Shader object for OpenGL. Try not to design it as a Template!
*/
class GLSLCompiler {
public:
  GLSLCompiler(ShaderStage stage, std::string filepath = "");
  /**
    Compile the shader and it's filepath.
  */
  vvoid Compile();
  vvoid Cleanup() { DeleteShader(static_cast<vuint32>(shader_id)); shader_id = -1; }
  vuint64 GetShaderId() { return shader_id; }
  vbool IsCompiled() { return compiled; }

  GLSLPreprocessor *GetPreprocessor() { return &preprocessor; }

  std::string GetFilePath() { return filepath; }
  vvoid SetFilePath(std::string path) { filepath = path; }

  ShaderStage GetShaderStage() { return shader_stage; }

private:
  vvoid LoadShaderFile();
  std::string filepath;
  ShaderStage shader_stage;
  
  vuint64 shader_id;
  vbool compiled;
  GLSLPreprocessor preprocessor;
};
} // vikr
#endif // __VIKR_GLSL_COMPILER_HPP