//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_device.hpp>
#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>
#include <vikr/graphics/gl4/gl4_vertexbuffer.hpp>
#include <vikr/graphics/gl4/gl4_renderpass.hpp>
#include <vikr/graphics/gl4/gl4_commandbuffer.hpp>
#include <vikr/graphics/gl4/gl4_graphics_pipeline_state.hpp>
#include <vikr/shader/glsl/gl4_cubemap.hpp>
#include <vikr/shader/glsl/glsl_shader.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/shader/glsl/gl4_texture1d.hpp>
#include <vikr/shader/glsl/gl4_texture2d.hpp>
#include <vikr/shader/glsl/gl4_texture3d.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/shader/stb/stb_image.h>

#include <vikr/util/vikr_log.hpp>
#include <cstddef>


namespace vikr {


/**
Storage for renderpasses inside this device.
*/
std::map<guid_t, std::unique_ptr<GL4RenderPass> > m_renderpasses;

/**
Storage for cubemaps within this device.
*/
std::map<guid_t, std::unique_ptr<GL4Cubemap> > m_cubemaps;

/**
Storage for vertex buffers inside this device.
*/
std::map<guid_t, std::unique_ptr<GL4Vertexbuffer> > m_vertexbuffers;

/**
Storage for framebuffer within this device.
*/
std::map<guid_t, std::unique_ptr<GL4Framebuffer> > m_framebuffers;


/**
*/
std::map<guid_t, std::unique_ptr<GLSLShader> > shaders;

/**
*/
std::map<guid_t, std::unique_ptr<GL4Texture> > textures;

/**
*/
std::map<guid_t, std::unique_ptr<GLSLShaderProgram> > shader_programs;

/**
*/
std::map<guid_t, std::unique_ptr<GL4GraphicsPipelineState> > graphicspipelinestates;


const std::string GL4RenderDevice::kGLSLShaderLanguage = "glsl";


GL4RenderDevice::GL4RenderDevice()
  : RenderDevice(vikr_API_OPENGL)
{
}


std::string GL4RenderDevice::GetShaderLanguage() {
  return kGLSLShaderLanguage;
}


/**
  Data is interleaved.
*/
Vertexbuffer *
GL4RenderDevice::CreateVertexbuffer(VertexUsageType type, 
  std::vector<Vertex> &vertices, std::vector<vuint32> &indices) 
{
  std::unique_ptr<GL4Vertexbuffer> gbo =
    std::make_unique<GL4Vertexbuffer>();
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
    std::vector<vreal32> data;
    
    for (vuint32 i = 0; i < vertices.size(); ++i) {
      data.push_back(vertices[i].position.x);
      data.push_back(vertices[i].position.y);
      data.push_back(vertices[i].position.z);

      data.push_back(vertices[i].normal.x);
      data.push_back(vertices[i].normal.y);
      data.push_back(vertices[i].normal.z);

      data.push_back(vertices[i].uv.x);
      data.push_back(vertices[i].uv.y);

      data.push_back(vertices[i].tangent.x);
      data.push_back(vertices[i].tangent.y);
      data.push_back(vertices[i].tangent.z);

      data.push_back(vertices[i].color.x);
      data.push_back(vertices[i].color.y);
      data.push_back(vertices[i].color.z);
    }
    /*
      TODO(): Need to optimize?
    */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), gl_type);
    if (!indices.empty()) {
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
        indices.size() * sizeof(GLuint), 
        indices.data(), 
        gl_type
      );
    }
    size_t offset = 0;
    GLuint stride = sizeof(Vertex);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    offset += sizeof(vreal32) * 3;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    offset += sizeof(vreal32) * 3;
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    offset += sizeof(vreal32) * 2;
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    offset += sizeof(vreal32) * 3;
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    glBindVertexArray(0);
    gbo->StoreVertexArrayId(vao);
    gbo->StoreVertexBufferId(vbo);
    gbo->StoreElementBufferId(ibo);
    VIKR_ASSERT(glGetError() == 0);
  }
  guid_t uid = gbo->GetUID();
  gbo->SetRenderDevice(this);
  m_vertexbuffers[uid] = std::move(gbo);
  return m_vertexbuffers[uid].get();
}


Framebuffer *GL4RenderDevice::CreateFramebuffer() {
  std::unique_ptr<GL4Framebuffer> framebuffer = 
    std::make_unique<GL4Framebuffer>();
  guid_t uid = framebuffer->GetUID();
  framebuffer->SetRenderDevice(this);
  m_framebuffers[uid] = std::move(framebuffer);
  return m_framebuffers[uid].get();
}


Cubemap *GL4RenderDevice::CreateCubemap() {
  std::unique_ptr<GL4Cubemap> cubemap =
    std::make_unique<GL4Cubemap>();
  guid_t uid = cubemap->GetUID();
  cubemap->SetRenderDevice(this);
  m_cubemaps[uid] = std::move(cubemap);
  return m_cubemaps[uid].get();
}


RenderPass *GL4RenderDevice::CreateRenderPass() {
  std::unique_ptr<GL4RenderPass> renderpass =
    std::make_unique<GL4RenderPass>();
  guid_t uid = renderpass->GetUID();
  renderpass->SetRenderDevice(this);
  m_renderpasses[uid] = std::move(renderpass);
  return m_renderpasses[uid].get();
}


Commandbuffer &GL4RenderDevice::CreateCommandbuffer() {
  GL4Commandbuffer buffer;
  buffer.SetRenderDevice(this);
  return std::move(buffer);
}


vbool GL4RenderDevice::DestroyRenderPass(guid_t id) {
  auto found = m_renderpasses.find(id);
  if (found != m_renderpasses.end()) {
    m_renderpasses.erase(found);
    return true;
  }
  return false;
}


vbool GL4RenderDevice::DestroyVertexbuffer(guid_t id) {
  auto found = m_vertexbuffers.find(id);
  if (found != m_vertexbuffers.end()) {
    found->second->Cleanup();
    m_vertexbuffers.erase(found);
    return true;
  }
  return false;
}


vbool GL4RenderDevice::DestroyCubemap(guid_t id) {
  auto found = m_cubemaps.find(id);
  if (found != m_cubemaps.end()) {
    found->second->Cleanup();
    m_cubemaps.erase(found);
    return true;  
  }
  return false;
}


vbool GL4RenderDevice::DestroyFramebuffer(guid_t id) {
  auto found = m_framebuffers.find(id);
  if (found != m_framebuffers.end()) {
    found->second->Cleanup();
    m_framebuffers.erase(found);
    return true;  
  }
  return false;
}



Shader *GL4RenderDevice::CreateShader(std::string name, ShaderStage stage) {
  std::unique_ptr<GLSLShader> shader = std::make_unique<GLSLShader>(stage);
  shader->SetName(name);

  guid_t id = shader->GetUID();
  shader->SetRenderDevice(this);
  shaders[shader->GetUID()] = std::move(shader);
  return static_cast<Shader *>(shaders[id].get());
}


Shader *GL4RenderDevice::GetShader(guid_t id) {
  if (shaders.find(id) != shaders.end()) {
    return static_cast<Shader *>(shaders[id].get());
  }
  return nullptr;
}


vbool GL4RenderDevice::DestroyShader(guid_t id) {
  vbool success = false;
  auto it = shaders.find(id);
  if (it != shaders.end()) {
    // cleanup first. Make sure the shader is not leaked.
    it->second->Cleanup();
    shaders.erase(it);
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "Shader id => " 
      + std::to_string(id) + " removed.");
    success = true;
  } 
  return success;
}


Texture *GL4RenderDevice::CreateTexture(
  std::string name, 
  TextureTarget target, 
  std::string filepath, 
  vbool alpha) 
{
  std::unique_ptr<GL4Texture> texture = nullptr;
  vint32 width = 0;
  vint32 height = 0;
  vint32 depth = 0;
  vbyte *bytecode = stbi_load(filepath.c_str(), &width, &height, &depth,
                              alpha ? STBI_rgb_alpha : STBI_rgb);
  switch(target) {
  case vikr_TARGET_1D: texture = std::make_unique<GL4Texture1D>(width); break;
  case vikr_TARGET_2D_MULTISAMPLE:
  case vikr_TARGET_2D: texture = std::make_unique<GL4Texture2D>(width, height); break;
  case vikr_TARGET_3D: texture = std::make_unique<GL4Texture3D>(width, height, depth); break;
  case vikr_TARGET_CUBEMAP: // not implemented yet.
  default: break;
  }
  guid_t id = texture->GetUID();
  if (texture) {
    if (target == vikr_TARGET_2D_MULTISAMPLE) {
      texture->SetMultisampled(true);
    }
    texture->SetBytecode(bytecode);
    //texture->Finalize(); // No need to tell the resource manager to finalize for us.
    texture->SetPath(filepath);
    texture->SetName(name);
    texture->SetRenderDevice(this);
    textures[texture->GetUID()] = std::move(texture);
  }
  return textures[id].get();
}


Texture *GL4RenderDevice::GetTexture(guid_t id) {
  return textures[id].get();
}


vbool GL4RenderDevice::DestroyTexture(guid_t id) {
  auto it = textures.find(id);
  vbool success = false;
  if (it != textures.end()) {
    // Cleanup first.
    it->second->Cleanup();
    textures.erase(it);
    success = true;
  }
  return success;
}


GraphicsPipelineState *GL4RenderDevice::CreateGraphicsPipelineState(vbool derivative) {
  std::unique_ptr<GL4GraphicsPipelineState> gl_pipeline =
    std::make_unique<GL4GraphicsPipelineState>();
  guid_t id = gl_pipeline->GetUID();
  gl_pipeline->SetRenderDevice(this);
  graphicspipelinestates[gl_pipeline->GetUID()] = std::move(gl_pipeline);
  return static_cast<GraphicsPipelineState *>(graphicspipelinestates[id].get());
}


GraphicsPipelineState *GL4RenderDevice::GetGraphicsPipelineState(guid_t id) {
  auto it = graphicspipelinestates.find(id);
  if (it != graphicspipelinestates.end()) {
    return graphicspipelinestates[id].get();
  }
  return nullptr;
}


vbool GL4RenderDevice::DestroyGraphicsPipelineState(guid_t id) {
  vbool success = false;
  auto it = graphicspipelinestates.find(id);
  if (it != graphicspipelinestates.end()) {
    graphicspipelinestates.erase(it);
    success = true;
  }
  return success;
}


vbool GL4RenderDevice::DestroyUniformbuffer(guid_t id) {
  return false;
}


Uniformbuffer *GL4RenderDevice::GetUniformbuffer(guid_t id) {
  return nullptr;
}


Uniformbuffer *GL4RenderDevice::CreateUniformbuffer() {
  return nullptr;
}


ComputePipelineState *GL4RenderDevice::CreateComputePipelineState(std::string name) {
  return nullptr;
}


ComputePipelineState *GL4RenderDevice::GetComputePipelineState(guid_t id) {
  return nullptr;
}


vbool GL4RenderDevice::DestroyComputePipelineState(guid_t id) {
  return false;
}


GraphicsHardwareInfo GL4RenderDevice::GetHardwareInformation() {
  GraphicsHardwareInfo info;
  info.shader_language = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
  info.renderer = (const char *)glGetString(GL_RENDERER);
  info.vendor = (const char *)glGetString(GL_VENDOR);
  info.version = (const char *)glGetString(GL_VERSION); 
  info.extensions = "none";//(const char *)glGetString(GL_EXTENSIONS);
  return info;
}


GraphicsPerformanceInfo GL4RenderDevice::GetPerformanceInformation() {
  GraphicsPerformanceInfo info;
  // Currently only way for nvidia, need to check for Intel and AMD.
  glGetIntegerv(GL_TOTAL_MEM_AVAILABLE_NVX, &info.total_mem_kb);
  glGetIntegerv(GL_CURRENT_MEM_AVAILABLE_NVX, &info.curr_available_mem_kb);
  return info;
}
} // vikr 