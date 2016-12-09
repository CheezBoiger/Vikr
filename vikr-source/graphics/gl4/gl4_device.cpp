//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_device.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


const std::string GL4RenderDevice::kGLSLShaderLanguage = "glsl";


GL4RenderDevice::GL4RenderDevice()
{
}


std::string GL4RenderDevice::GetShaderLanguage() {
  return kGLSLShaderLanguage;
}


Texture *GL4RenderDevice::GenerateTexture(
  std::string path, TextureTarget target, vbool alpha) 
{
  return manager.CreateTexture(target, path, alpha);
}


Shader *GL4RenderDevice::GetShader(std::string name) {
  return manager.GetShader(name);
}


vvoid GL4RenderDevice::StoreShader(
  std::string name, std::string vs, 
  std::string fs, std::string include) 
{
  vint32 success =  manager.StoreShader(name, vs, fs, include);
  if (!success) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Error storing shader!");
  }
}


Material *GL4RenderDevice::CreateMaterial() {
  return manager.CreateMaterial();
}


vuint32 GL4RenderDevice::CreateVertexBufferId(std::vector<Vertex> &vertices, VertexUsageType type) {
  vuint32 vbo = 0;
  if (!vertices.empty()) {
    GLenum gl_type;
    switch (type) {
      case vikr_STATIC:
        gl_type = GL_STATIC_DRAW;
      break;
      case vikr_DYNAMIC:
        gl_type = GL_DYNAMIC_DRAW;
      break;
      default:
        gl_type = GL_STATIC_DRAW;
      break;
    }
    size_t stride = 3 * sizeof(vreal32);
    stride += 3 * sizeof(vreal32);
    stride += 2 * sizeof(vreal32);
    vuint32 offset = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vreal32), &vertices[0], gl_type);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (vvoid *)offset);
    offset += 3 * sizeof(vreal32);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (vvoid *)offset);
    offset += 3 * sizeof(vreal32);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (vvoid *)offset);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  return vbo;
}


vuint32 GL4RenderDevice::CreateElementBufferId(std::vector<vuint32> &indices, VertexUsageType type) {
  vuint32 ibo = 0;
  if (!indices.empty()) {
    GLenum gl_type;
    switch (type) {
      case vikr_STATIC:
        gl_type = GL_STATIC_DRAW;
      break;
      case vikr_DYNAMIC:
        gl_type = GL_DYNAMIC_DRAW;
      break;
      default: 
        gl_type = GL_STATIC_DRAW;
      break;
    }
    glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(vuint32), indices.data(), gl_type);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  return ibo;
}


Framebuffer *GL4RenderDevice::GenerateFramebuffer() {
  return nullptr; // for now.
}
} // vikr 