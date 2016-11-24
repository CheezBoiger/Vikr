//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLSL_COMPILER_H
#define __VIKR_GLSL_COMPILER_H

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
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

private:
  vvoid LoadShaderFile(std::string filepath);
  VikrGLPipelineStage pipeline_stage;
  
  vuint32 shader_id;
  vbool compiled;
};
} // vikr
#endif // __VIKR_GLSL_COMPILER_HPP