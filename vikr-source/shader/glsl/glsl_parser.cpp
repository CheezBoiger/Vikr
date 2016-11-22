//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#include <shader/glsl/glsl_parser.hpp>
#include <shader/shader.hpp>

namespace vikr {


GLSLParser::GLSLParser(Shader *shader)
  : ShaderParser(shader)
{
}


vvoid GLSLParser::ParseActiveUniforms() {
  vint32 n_uniforms;
  GetProgramiv(shader_ref->GetProgram(), GL_ACTIVE_UNIFORMS, &n_uniforms);
  if(n_uniforms > 0) {
    vint32 length;
    GetProgramiv(shader_ref->GetProgram(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
    if(length > 0) {
      char buf[256];
      for(vint32 i = 0; i < n_uniforms; ++i) {
        Uniform uniform;
        GLenum type;
        GetActiveUniform(shader_ref->GetProgram(), i, length, nullptr, &uniform.uniform_size, &type, buf);
        uniform.uniform_name = std::string(buf);
        uniform.uniform_location = GetUniformLocation(shader_ref->GetProgram(), buf);
        shader_ref->InsertUniform(uniform);
      }
    }
  }
}


vvoid GLSLParser::ParseActiveAttributes() {
  vint32 n_attribs;
  char buf[256];
  GetProgramiv(shader_ref->GetProgram(), GL_ACTIVE_ATTRIBUTES, &n_attribs);
  for(vint32 i = 0; i < n_attribs; ++i) {
    VertexAttrib attrib;
    GLenum type;
    GetActiveAttrib(shader_ref->GetProgram(), i, sizeof(buf), 0, &attrib.attrib_size, &type, buf);
    attrib.attrib_name = std::string(buf);
    attrib.attrib_location = GetAttribLocation(shader_ref->GetProgram(), buf);
    shader_ref->InsertAttribute(attrib);
  }
}
}