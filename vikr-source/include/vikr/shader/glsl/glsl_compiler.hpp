//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLSL_COMPILER_H
#define __VIKR_GLSL_COMPILER_H

#include <vikr/shader/glsl/glsl_preprocessor.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <string>


namespace vikr {


/**
  Determines the pipeline stage of the GLSL shader.
*/
enum VikrGLPipelineStage {
  vikr_VERTEX_SHADER = GL_VERTEX_SHADER,
  vikr_FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
  vikr_GEOMETRY_SHADER = GL_GEOMETRY_SHADER
};


/**
  GLSL Shader object for OpenGL. Try not to design it as a Template!
*/
class GLSLCompiler {
public:
  GLSLCompiler(VikrGLPipelineStage stage = vikr_VERTEX_SHADER, std::string filepath = "");
  /**
    Compile the shader and it's filepath.
  */
  vvoid Compile();
  vvoid Cleanup() { DeleteShader(shader_id); }
  VikrGLPipelineStage GetPipelineStage() { return pipeline_stage; }
  vuint32 GetShaderId() { return shader_id; }
  vbool IsCompiled() { return compiled; }

  GLSLPreprocessor *GetPreprocessor() { return &preprocessor; }

  std::string GetFilePath() { return filepath; }
  vvoid SetFilePath(std::string path) { filepath = path; }

private:
  vvoid LoadShaderFile();
  std::string filepath;
  VikrGLPipelineStage pipeline_stage;
  
  vuint32 shader_id;
  vbool compiled;
  GLSLPreprocessor preprocessor;
};
} // vikr
#endif // __VIKR_GLSL_COMPILER_HPP