//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SHADER_HPP
#define __VIKR_SHADER_HPP

#include <shader/ishader.hpp>
#include <unordered_map>
#include <string>

namespace vikr {


class GLShader;


enum ShaderUniformType {
  vikr_TEXTURE2D,
  vikr_TEXTURE3D,
  vikr_SAMPLER2D,
  vikr_SAMPLER3D,
  vikr_SAMPLERCUBE,
  vikr_INT,
  vikr_FLOAT,
  vikr_BOOL,
  vikr_VEC2,
  vikr_VEC3,
  vikr_VEC4,
  vikr_MAT2,
  vikr_MAT3,
  vikr_MAT4
};


struct Uniform {
  std::string       uniform_name;
  ShaderUniformType uniform_type;
  vuint32           uniform_location;
};


struct VertexAttrib {
  std::string       attrib_name;
  ShaderUniformType attrib_type;
  vuint32           attrib_location;
};

/**
  For now it only works with OpenGL, Spir-V not yet implemented!
*/
class Shader {
public:
  Shader();

  vvoid Link(IShader* vs, IShader* fs, IShader* gs = nullptr);
  vvoid Use() { UseProgram(program); }
  inline vuint32 GetProgram() { return program; }
  inline vbool IsLinked() { return is_linked; }
private:
  vuint32 program;
  vbool is_linked;
  std::unordered_map<std::string, std::pair<std::string, Uniform> >      m_uniforms;
  std::unordered_map<std::string, std::pair<std::string, VertexAttrib> > m_attribs;
};
} // vikr
#endif // __VIKR_SHADER_HPP