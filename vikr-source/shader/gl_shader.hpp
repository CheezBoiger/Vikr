//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_SHADER_H
#define __VIKR_GL_SHADER_H

#include <shader/ishader.hpp>
#include <string>


namespace vikr {


/**
  Determines the pipeline stage of the GLSL shader.
*/
enum VikrPipelineStage {
  vikr_VERTEX_SHADER = GL_VERTEX_SHADER,
  vikr_FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
  vikr_GEOMETRY_SHADER = GL_GEOMETRY_SHADER
};


/**
  GLSL Shader object for OpenGL. Try not to design it as a Template!
*/
class GLShader {
public:
  GLShader(VikrPipelineStage stage = vikr_VERTEX_SHADER, std::string filepath = "");

  vvoid Compile();
  vvoid Cleanup() { glDeleteShader(shader_id); }
  VikrPipelineStage GetPipelineStage() { return pipeline_stage; }
  vuint32 GetShaderId() { return shader_id; }
  vbool IsCompiled() { return compiled; }
private:
  vvoid LoadShaderFile(std::string filepath);
  VikrPipelineStage pipeline_stage;
  
  vuint32 shader_id;
  vbool compiled;
};
} // vikr
#endif // __VIKR_GL_SHADER_H