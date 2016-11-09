//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_SHADER_H
#define __VIKR_GL_SHADER_H

#include <platform/vikr_types.hpp>
#include <string>
#include <sstream>

namespace vikr {



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
  GLShader(VikrPipelineStage stage = vikr_VERTEX_SHADER);
private:
  
};


class GLProgram {
public:
private:
};
} // vikr
#endif // __VIKR_GL_SHADER_H