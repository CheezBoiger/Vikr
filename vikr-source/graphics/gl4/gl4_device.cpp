//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_device.hpp>
#include <graphics/gl4/gl4_rendertarget.hpp>
#include <graphics/gl4/gl4_framebuffer.hpp>
#include <graphics/gl4/gl4_vertexbuffer.hpp>
#include <shader/glsl/gl_cubemap.hpp>
#include <util/vikr_log.hpp>
#include <cstddef>


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


Material *GL4RenderDevice::CreateMaterial(std::string name) {
  return manager.CreateMaterial(name);
}


/**
  Data is interleaved.
*/
std::unique_ptr<Vertexbuffer> 
GL4RenderDevice::CreateVertexbuffer(
  std::vector<Vertex> &vertices, std::vector<vuint32> &indices, VertexUsageType type) 
{
  GL4Vertexbuffer gbo;
  vuint32 vbo;
  vuint32 vao;
  vuint32 ibo = -1;
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
    /*
      TODO(): Need to optimize?
    */
    std::vector<vreal32> data;
    for(vuint32 i = 0; i < vertices.size(); ++i) {
      data.push_back(vertices[i].position.x);
      data.push_back(vertices[i].position.y);
      data.push_back(vertices[i].position.z);
      data.push_back(vertices[i].normal.x);
      data.push_back(vertices[i].normal.y);
      data.push_back(vertices[i].normal.z);
      data.push_back(vertices[i].uv.x);
      data.push_back(vertices[i].uv.y);
    }
    vuint32 offset = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(vreal32), &data[0], gl_type);
    if(!indices.empty()) {
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(vuint32), &indices[0], gl_type);
    }
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (vvoid *)offset);
    offset += sizeof(vreal32) * 3;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (vvoid *)offset);
    offset += sizeof(vreal32) * 3;
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (vvoid *)offset);
    offset += sizeof(vreal32) * 2;
    glBindVertexArray(0);
    gbo.StoreVertexArrayId(vao);
    gbo.StoreVertexBufferId(vbo);
    gbo.StoreElementBufferId(ibo);
  }

  return std::make_unique<GL4Vertexbuffer>(std::move(gbo));
}


std::unique_ptr<Framebuffer> GL4RenderDevice::CreateFramebuffer() {
  return std::make_unique<GL4Framebuffer>(); // for now.
}


std::unique_ptr<Renderbuffer> GL4RenderDevice::CreateRenderbuffer(vuint32 width, vuint32 height) {
  return std::make_unique<GL4Renderbuffer>(width, height);
}


std::unique_ptr<RenderTexture> GL4RenderDevice::CreateRenderTexture(std::string t_name, 
  vuint32 width, vuint32 height, vbool alpha, DataTypeFormat precision) 
{
  return std::make_unique<GL4RenderTexture>(t_name, width, height, alpha, precision);
}


std::unique_ptr<Cubemap> GL4RenderDevice::CreateCubemap() {
  return std::make_unique<GLCubemap>();
}
} // vikr 