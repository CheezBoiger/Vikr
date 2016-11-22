//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLSL_COMPILER_H
#define __VIKR_GLSL_COMPILER_H

#include <shader/shader_compiler.hpp>
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
class GLSLCompiler : public IShaderCompiler {
public:
  GLSLCompiler(VikrGLPipelineStage stage = vikr_VERTEX_SHADER, std::string filepath = "");

  vvoid Compile() override;
  vvoid Cleanup() override { DeleteShader(shader_id); }
  VikrGLPipelineStage GetPipelineStage() { return pipeline_stage; }
  vuint32 GetShaderId() override { return shader_id; }
  vbool IsCompiled() override { return compiled; }
  ShaderCompilerType GetShaderType() override { return shader_type; }

private:
  vvoid LoadShaderFile(std::string filepath);
  VikrGLPipelineStage pipeline_stage;
  ShaderCompilerType shader_type;
  
  vuint32 shader_id;
  vbool compiled;
};
} // vikr
#endif // __VIKR_GLSL_COMPILER_HPP