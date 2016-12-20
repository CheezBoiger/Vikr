//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_rendertarget.hpp>
#include <lighting/light.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


GL4RenderTexture::GL4RenderTexture(std::string t_name, vuint32 width, 
  vuint32 height, vbool alpha, DataTypeFormat precision)
  : RenderTexture(vikr_PIPELINE_OPENGL, width, height, alpha)
{
  m_texture = std::make_unique<GLTexture2D>(width, height);
  m_texture->SetName(t_name);
  m_texture->SetFilterMin(TextureFilterMode::vikr_TEXTURE_NEAREST);
  m_texture->SetFilterMax(TextureFilterMode::vikr_TEXTURE_NEAREST);
  m_texture->SetFormat(alpha ? TextureFormat::vikr_RGBA : TextureFormat::vikr_RGB);
  m_texture->SetInternalFormat(alpha ? TextureFormat::vikr_RGBA : TextureFormat::vikr_RGB16F);
  m_texture->SetDataTypeFormat(precision);
  m_texture->SetMipmapping(false);
  m_texture->Create(nullptr);
}


GL4Renderbuffer::GL4Renderbuffer(vuint32 width, vuint32 height)
  : Renderbuffer(vikr_PIPELINE_OPENGL, width, height)
{
  // Render my buffers.
  glGenRenderbuffers(1, &m_rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


GL4RenderDepthTexture::GL4RenderDepthTexture(std::string name, vuint32 width, 
  vuint32 height, DataTypeFormat precision)
  : RenderDepthTexture(vikr_PIPELINE_OPENGL, width, height)
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