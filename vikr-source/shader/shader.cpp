//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <shader/shader.hpp>
#include <shader/gl_shader.hpp>
#include <util/vikr_log.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace vikr {


Shader::Shader()
  : program(CreateProgram())
  , is_linked(false)
{

}


vvoid Shader::Link(IShader* vs, IShader* fs, IShader* gs) {
  vint32 success;
  GLchar log[1024];
  if(!vs->IsCompiled()) {
    vs->Compile();
  }
  if(!fs->IsCompiled()) {
    fs->Compile();
  }
  if(gs != nullptr && !gs->IsCompiled()) {
    gs->Compile();
  }
  AttachShader(program, vs->GetShaderId());
  AttachShader(program, fs->GetShaderId());
  LinkProgram(program);
  GetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success) {
    GetProgramInfoLog(program, 1024, NULL, log);
    VikrLog::DisplayMessage(vikr::VIKR_ERROR, std::string(log));
  }
  vs->Cleanup();
  fs->Cleanup();
  if(gs != nullptr) {
    gs->Cleanup();
  }
  if (success) {
    ParseActiveUniforms();
    ParseActiveAttribs();
    is_linked = true;
  }
}


vvoid Shader::ParseActiveUniforms() {
  vint32 n_uniforms;
  char buf[256];
  GetProgramiv(program, GL_ACTIVE_UNIFORMS, &n_uniforms);
  for (vint32 i = 0; i < n_uniforms; ++i) {
    Uniform uniform;
    GLenum type;
    GetActiveUniform(program, i, sizeof(buf), 0, &uniform.uniform_size, &type, buf);
    uniform.uniform_name = std::string(buf);
    uniform.uniform_location = GetUniformLocation(program, buf);
    m_uniforms[uniform.uniform_name] = std::make_pair(uniform.uniform_name, uniform);
  } 
}


vvoid Shader::ParseActiveAttribs() {
  vint32 n_attribs;
  char buf[256];
  GetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &n_attribs);
  for (vint32 i = 0; i < n_attribs; ++i) {
    VertexAttrib attrib;
    GLenum type;
    GetActiveAttrib(program, i, sizeof(buf), 0, &attrib.attrib_size, &type, buf);
    attrib.attrib_name = std::string(buf);
    attrib.attrib_location = GetAttribLocation(program, buf);
    m_attribs[attrib.attrib_name] = std::make_pair(attrib.attrib_name, attrib);
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