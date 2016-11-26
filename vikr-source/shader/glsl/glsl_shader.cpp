//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/glsl_shader.hpp>
#include <shader/glsl/glsl_compiler.hpp>
#include <shader/glsl/glsl_linker.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <util/vikr_log.hpp>

namespace vikr {


GLSLShader::GLSLShader()
{
  shader_type = vikr_GLSL;
}


vvoid GLSLShader::Compile(std::string vs, std::string fs, std::string gs) {
  GLSLCompiler vert(vikr_VERTEX_SHADER, vs);
  GLSLCompiler frag(vikr_FRAGMENT_SHADER, fs);
  GLSLCompiler geo(vikr_GEOMETRY_SHADER, gs);
  GLSLLinker linker(this);
  vert.GetPreprocessor()->SetSourceDirectory(include_searchpath);
  frag.GetPreprocessor()->SetSourceDirectory(include_searchpath);
  vert.Compile();
  frag.Compile();
  if (!gs.empty()) {
    geo.Compile();
  }
  if (vert.IsCompiled() && frag.IsCompiled()) {
    shader_id = CreateProgram();
    linker.Link(&vert, &frag, &geo);
    if (!linker.IsLinked()) {
      VikrLog::DisplayMessage(VIKR_ERROR, "Shader was not linked!");
    }
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "Shaders unsuccessfully compiled!");
  }
  is_linked = linker.IsLinked();
}


vvoid GLSLShader::SetValue(std::string name, vint32 value) {
  Uniform1i(GetUniformLocation(shader_id, name.c_str()), value);
}


vvoid GLSLShader::SetValue(std::string name, vbool value) {
  SetValue(name, (vint32)value);
}


vvoid GLSLShader::SetValue(std::string name, vreal32 value) {
  Uniform1f(GetUniformLocation(shader_id, name.c_str()), value);
}


vvoid GLSLShader::SetValue(std::string name, vreal64 value) {
  Uniform1d(GetUniformLocation(shader_id, name.c_str()), value);
}


vvoid GLSLShader::SetValue(std::string name, glm::vec2 value) {
  Uniform2fv(GetUniformLocation(shader_id, name.c_str()), 1, glm::value_ptr(value));
}


vvoid GLSLShader::SetValue(std::string name, glm::vec3 value) {
  Uniform3fv(GetUniformLocation(shader_id, name.c_str()), 1, glm::value_ptr(value));
}


vvoid GLSLShader::SetValue(std::string name, glm::vec4 value) {
  Uniform4fv(GetUniformLocation(shader_id, name.c_str()), 1, glm::value_ptr(value));
}


vvoid GLSLShader::SetValue(std::string name, glm::mat2 value) {
  UniformMatrix2fv(GetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}


vvoid GLSLShader::SetValue(std::string name, glm::mat3 value) {
  UniformMatrix3fv(GetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}


vvoid GLSLShader::SetValue(std::string name, glm::mat4 value) {
  UniformMatrix4fv(GetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
} // vikr