//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_device.hpp>
#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>
#include <vikr/graphics/gl4/gl4_vertexbuffer.hpp>
#include <vikr/graphics/gl4/gl4_renderpass.hpp>
#include <vikr/graphics/gl4/gl4_commandbuffer.hpp>
#include <vikr/graphics/gl4/gl4_pipeline_state.hpp>
#include <vikr/shader/glsl/gl_cubemap.hpp>
#include <vikr/util/vikr_log.hpp>
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
  std::string fs, std::string include, std::string gs) 
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
GL4RenderDevice::CreateVertexbuffer(VertexContainer &vertices) 
{
  GL4Vertexbuffer gbo;
  vuint32 vbo;
  vuint32 vao;
  vuint32 ibo = -1;
  if (!vertices.positions.empty()) {
    GLenum gl_type;
    switch (vertices.usage_type) {
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
    vuint32 count = 0;
    data.resize(vertices.positions.size() + vertices.normals.size() +
      vertices.uvs.size() + vertices.tangents.size() + vertices.bitangents.size());
    for (vuint32 i = 0; i < vertices.positions.size(); ++i) {
      data[count++] = vertices.positions[i];
    }
    for (vuint32 i = 0; i < vertices.normals.size(); ++i) {
      data[count++] = vertices.normals[i];
    }
    for (vuint32 i = 0; i < vertices.uvs.size(); ++i) {
      data[count++] = vertices.uvs[i];
    }
    for (vuint32 i = 0; i < vertices.tangents.size(); ++i) {
      data[count++] = vertices.tangents[i];
    }
    for (vuint32 i = 0; i < vertices.bitangents.size(); ++i) {
      data[count++] = vertices.bitangents[i];
    }
    vuint32 offset = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(vreal32), &data[0], gl_type);
    if (!vertices.indices.empty()) {
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
        vertices.indices.size() * sizeof(vuint32), 
        &vertices.indices[0], 
        gl_type
      );
    }
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
    offset += sizeof(vreal32) * vertices.positions.size();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
    offset += sizeof(vreal32) * vertices.normals.size();
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
    offset += sizeof(vreal32) * vertices.uvs.size();
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
    offset += sizeof(vreal32) * vertices.tangents.size();
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
    offset += sizeof(vreal32) * vertices.bitangents.size();
    glBindVertexArray(0);
    gbo.StoreVertexArrayId(vao);
    gbo.StoreVertexBufferId(vbo);
    gbo.StoreElementBufferId(ibo);
    vertices.size = offset;
  }

  return std::make_unique<GL4Vertexbuffer>(std::move(gbo));
}


std::unique_ptr<Framebuffer> GL4RenderDevice::CreateFramebuffer() {
  return std::make_unique<GL4Framebuffer>(); // for now.
}


std::unique_ptr<Renderbuffer> GL4RenderDevice::CreateRenderbuffer(vuint32 width, vuint32 height, vbool multisample) {
  return std::make_unique<GL4Renderbuffer>(width, height, multisample);
}


std::unique_ptr<RenderTexture> GL4RenderDevice::CreateRenderTexture(std::string t_name, 
  vuint32 width, vuint32 height, vbool alpha, vbool multisample, DataTypeFormat precision) 
{
  return std::make_unique<GL4RenderTexture>(t_name, width, height, alpha, multisample, precision);
}


std::unique_ptr<Cubemap> GL4RenderDevice::CreateCubemap() {
  return std::make_unique<GLCubemap>();
}


std::unique_ptr<RenderPass> GL4RenderDevice::CreateRenderPass() {
  return std::make_unique<GL4RenderPass>();
}


std::unique_ptr<Commandbuffer> GL4RenderDevice::CreateCommandbuffer() {
  return std::make_unique<GL4Commandbuffer>();
}
} // vikr 