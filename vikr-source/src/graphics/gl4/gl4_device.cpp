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


std::map<guid_t, std::unique_ptr<GL4CommandbufferList> > m_commandbufferlists;


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
  return manager.CreateTexture("", target, path, alpha);
}


Material *GL4RenderDevice::CreateMaterial(std::string name) {
  return manager.CreateMaterial(name);
}


/**
  Data is interleaved.
*/
Vertexbuffer *
GL4RenderDevice::CreateVertexbuffer(VertexContainer &vertices) 
{
  std::unique_ptr<GL4Vertexbuffer> gbo =
    std::make_unique<GL4Vertexbuffer>();
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
      vertices.uvs.size() + vertices.tangents.size() + 
      vertices.bitangents.size() + vertices.colors.size());
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
    for (vuint32 i = 0; i < vertices.colors.size(); ++i) {
      data[count++] = vertices.colors[i];
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
    if (!vertices.normals.empty()) {
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
      offset += sizeof(vreal32) * vertices.normals.size();
    }

    if (!vertices.uvs.empty()) {
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
      offset += sizeof(vreal32) * vertices.uvs.size();
    }

    if (!vertices.tangents.empty()) {
      glEnableVertexAttribArray(3);
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
      offset += sizeof(vreal32) * vertices.tangents.size();
    }

    if (!vertices.bitangents.empty()) {
      glEnableVertexAttribArray(4);
      glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
      offset += sizeof(vreal32) * vertices.bitangents.size();
    }

    if (!vertices.colors.empty()) {
      glEnableVertexAttribArray(5);
      glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (vvoid *)offset);
      offset += sizeof(vreal32) * vertices.colors.size();
    }
    glBindVertexArray(0);
    gbo->StoreVertexArrayId(vao);
    gbo->StoreVertexBufferId(vbo);
    gbo->StoreElementBufferId(ibo);
    vertices.size = data.size();

    VIKR_ASSERT(glGetError() == 0);
  }
  guid_t uid = gbo->GetUID();
  m_vertexbuffers[uid] = std::move(gbo);
  return m_vertexbuffers[uid].get();
}


Framebuffer *GL4RenderDevice::CreateFramebuffer() {
  std::unique_ptr<GL4Framebuffer> framebuffer = 
    std::make_unique<GL4Framebuffer>();
  guid_t uid = framebuffer->GetUID();
  m_framebuffers[uid] = std::move(framebuffer);
  return m_framebuffers[uid].get();
}


Cubemap *GL4RenderDevice::CreateCubemap() {
  std::unique_ptr<GL4Cubemap> cubemap =
    std::make_unique<GL4Cubemap>();
  guid_t uid = cubemap->GetUID();
  m_cubemaps[uid] = std::move(cubemap);
  return m_cubemaps[uid].get();
}


RenderPass *GL4RenderDevice::CreateRenderPass() {
  std::unique_ptr<GL4RenderPass> renderpass =
    std::make_unique<GL4RenderPass>();
  guid_t uid = renderpass->GetUID();
  m_renderpasses[uid] = std::move(renderpass);
  return m_renderpasses[uid].get();
}


Commandbuffer &GL4RenderDevice::CreateCommandbuffer(CommandbufferList *list) {
  GL4CommandbufferList *glist = static_cast<GL4CommandbufferList *>(list);
  GL4Commandbuffer buffer;
  glist->PushBack(buffer);
  return (*glist->Raw().back());
}


CommandbufferList *GL4RenderDevice::CreateCommandbufferList() {
  std::unique_ptr<GL4CommandbufferList> list = 
    std::make_unique<GL4CommandbufferList>();
  guid_t uid = list->GetUID();
  m_commandbufferlists[uid] = std::move(list);
  return m_commandbufferlists[uid].get();
}


vbool GL4RenderDevice::DestroyRenderPass(guid_t id) {
  auto found = m_renderpasses.find(id);
  if (found != m_renderpasses.end()) {
    m_renderpasses.erase(found);
    return true;
  }
  return false;
}


vbool GL4RenderDevice::DestroyCommandbufferList(guid_t id) {
  auto found = m_commandbufferlists.find(id);
  if (found != m_commandbufferlists.end()) {
    m_commandbufferlists.erase(found);
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
} // vikr 