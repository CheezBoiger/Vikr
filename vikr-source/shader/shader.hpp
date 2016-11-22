//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SHADER_HPP
#define __VIKR_SHADER_HPP

#include <shader/shader_compiler.hpp>
#include <shader/shader_parser.hpp>
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

namespace vikr {


/**
  We determine the uniform type for our Uniform object
  within the shader.
*/
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


/**
  Calculated uniforms in GLSL file.
*/
struct Uniform {
  std::string       uniform_name;
  ShaderUniformType uniform_type;
  vint32            uniform_size;
  vuint32           uniform_location;
};


/** 
  Vertex Attributes.
*/
struct VertexAttrib {
  std::string       attrib_name;
  ShaderUniformType attrib_type;
  vint32            attrib_size;
  vuint32           attrib_location;
};

/**
  For now it only works with OpenGL, Spir-V not yet implemented!
*/
class Shader {
public:
  Shader();
  Shader(Shader&& shader) = default;
  Shader& operator=(Shader&& shader) = default;

  vvoid Link(IShaderCompiler* vs, IShaderCompiler* fs, IShaderCompiler* gs = nullptr);
  vvoid Use() { UseProgram(program); }
  inline vuint32 GetProgram() { return program; }
  inline vbool IsLinked() { return is_linked; }

  vvoid SetInt(std::string name, vint32 value);
  vvoid SetBool(std::string name, vbool value);
  vvoid SetVector4fv(std::string name, glm::vec4 value);
  vvoid SetVector3fv(std::string name, glm::vec3 value);
  vvoid SetVector2fv(std::string name, glm::vec2 value);
  vvoid SetFloat(std::string name, vreal32 value);
  vvoid SetDouble(std::string name, vreal64 value);
  vvoid SetMat4(std::string name, glm::mat4 value);
  vvoid SetMat3(std::string name, glm::mat3 value);
  vvoid SetMat2(std::string name, glm::mat2 value);


  vint32 GetNumberOfUniforms() { return m_uniforms.size(); }
  vint32 GetNumberOfAttribs() { return m_attribs.size(); }

  ShaderCompilerType GetShaderType() { return shader_type; }

  vvoid InsertUniform(Uniform &uniform);
  vvoid InsertAttribute(VertexAttrib &attrib);

  Uniform *GetUniform(std::string name);
  VertexAttrib *GetAttrib(std::string name);

private:
  vvoid ParseActiveUniforms();
  vvoid ParseActiveAttribs();

  ShaderCompilerType shader_type;
  std::unique_ptr<ShaderParser> m_parser;

  vuint32 program;
  vbool is_linked;
  std::unordered_map<std::string, std::pair<std::string, Uniform> >      m_uniforms;
  std::unordered_map<std::string, std::pair<std::string, VertexAttrib> > m_attribs;
  VIKR_DISALLOW_COPY_AND_ASSIGN(Shader);
};
} // vikr
#endif // __VIKR_SHADER_HPP