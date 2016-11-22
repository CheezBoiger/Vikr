//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <shader/shader.hpp>
#include <shader/glsl/glsl_compiler.hpp>
#include <util/vikr_log.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader/shader_parser.hpp>
#include <shader/glsl/glsl_parser.hpp>
#include <shader/glsl/glsl_linker.hpp>
#include <shader/spirv/spirv_compiler.hpp>


namespace vikr {


Shader::Shader()
  : program(CreateProgram())
  , is_linked(false)
  , shader_type(vikr_GLSL)
  , m_parser(nullptr)
{

}


vvoid Shader::Link(IShaderCompiler *vs, IShaderCompiler *fs, IShaderCompiler *gs) {
  if (!vs || !fs) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Vertex or Fragment shader was not specified!");
    return;
  }
  vint32 success = 0;
  switch (vs->GetShaderType()) {
    case vikr_GLSL: { 
      GLSLParser parse(this);
      GLSLLinker linker(this);
      m_parser = std::make_unique<GLSLParser>(std::move(parse));
      success = linker.Link(vs, fs, gs);
    }
    break;
    case vikr_SPIRV: {
    }
    break;
  }
  if (success) {
    ParseActiveUniforms();
    ParseActiveAttribs();
    is_linked = true;
  }
}


vvoid Shader::ParseActiveUniforms() {
  if (m_parser) {
    m_parser->ParseActiveUniforms();
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "No Parser initialized!");
  }
}


vvoid Shader::InsertUniform(Uniform &uniform) {
  m_uniforms[uniform.uniform_name] = 
        std::make_pair(uniform.uniform_name, uniform);
}


vvoid Shader::InsertAttribute(VertexAttrib &attrib) {
  m_attribs[attrib.attrib_name] = 
      std::make_pair(attrib.attrib_name, std::move(attrib));
}


Uniform *Shader::GetUniform(std::string name) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    return &m_uniforms[name].second;
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "No uniform by the name " + name);
  }
  return nullptr;
}


VertexAttrib *Shader::GetAttrib(std::string name) {
  if (m_attribs.find(name) != m_attribs.end()) {
    return &m_attribs[name].second;
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "No uniform by the name " + name);
  }
  return nullptr;
}


vvoid Shader::ParseActiveAttribs() {
  if (m_parser) {
    m_parser->ParseActiveAttributes();
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "No parser initialized!");
  }
}


vvoid Shader::SetMat4(std::string name, glm::mat4 value) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    UniformMatrix4fv(m_uniforms[name].second.uniform_location, 1, GL_FALSE, glm::value_ptr(value));
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetMat3(std::string name, glm::mat3 value) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    UniformMatrix3fv(m_uniforms[name].second.uniform_location, 1, GL_FALSE, glm::value_ptr(value));
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetMat2(std::string name, glm::mat2 value) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    UniformMatrix2fv(m_uniforms[name].second.uniform_location, 1, GL_FALSE, glm::value_ptr(value));
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetFloat(std::string name, vreal32 value) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    Uniform1f(m_uniforms[name].second.uniform_location, value);
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetInt(std::string name, vint32 value) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    Uniform1i(m_uniforms[name].second.uniform_location, value);
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetVector4fv(std::string name, glm::vec4 value) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    Uniform4fv(m_uniforms[name].second.uniform_location, 1, glm::value_ptr(value));
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetVector3fv(std::string name, glm::vec3 value) {
  if(m_uniforms.find(name) != m_uniforms.end()) {
    Uniform3fv(m_uniforms[name].second.uniform_location, 1, glm::value_ptr(value));
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetVector2fv(std::string name, glm::vec2 value) {
  if(m_uniforms.find(name) != m_uniforms.end()) {
    Uniform2fv(m_uniforms[name].second.uniform_location, 1, glm::value_ptr(value));
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetDouble(std::string name, vreal64 value) {
  if (m_uniforms.find(name) != m_uniforms.end()) {
    Uniform1d(m_uniforms[name].second.uniform_location, 1, value);
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "uniform " + name + " not found!");
  }
}


vvoid Shader::SetBool(std::string name, vbool value) {
  SetInt(name, value);
}
} // vikr