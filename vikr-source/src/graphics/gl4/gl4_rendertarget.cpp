//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/lighting/light.hpp>
#include <vikr/shader/glsl/gl_texture2d.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


GL4RenderTexture::GL4RenderTexture(std::string t_name, vuint32 width, 
  vuint32 height, vbool alpha, vbool multisampled, DataTypeFormat precision)
  : RenderTexture(vikr_PIPELINE_OPENGL, width, height, alpha, multisampled)
{
  m_texture = std::make_unique<GLTexture2D>(width, height);
  m_texture->SetName(t_name);
  m_texture->SetFilterMin(TextureFilterMode::vikr_TEXTURE_NEAREST);
  m_texture->SetFilterMax(TextureFilterMode::vikr_TEXTURE_NEAREST);
  m_texture->SetFormat(alpha ? TextureFormat::vikr_RGBA : TextureFormat::vikr_RGB);
  m_texture->SetInternalFormat(alpha ? TextureFormat::vikr_RGBA : TextureFormat::vikr_RGB16F);
  m_texture->SetDataTypeFormat(precision);
  m_texture->SetMipmapping(false);
  if (multisampled) {
    m_texture->SetMultisampled(true);
  }
  
  m_texture->SetByteCode(nullptr);
  m_texture->Finalize();
}


GL4Renderbuffer::GL4Renderbuffer(vuint32 width, vuint32 height, vbool multisampled)
  : Renderbuffer(vikr_PIPELINE_OPENGL, width, height, multisampled)
{
  // Render my buffers.
  glGenRenderbuffers(1, &m_rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
  if (multisampled) {
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 0, GL_DEPTH_COMPONENT, width, height);
  } else {
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  }
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


GL4RenderDepthTexture::GL4RenderDepthTexture(std::string name, vuint32 width, 
  vuint32 height, vbool multisampled, DataTypeFormat precision)
  : RenderDepthTexture(vikr_PIPELINE_OPENGL, width, height, multisampled)
{
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
               SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
} // vikr