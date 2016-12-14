//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_rendertarget.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


GL4RenderTexture::GL4RenderTexture(vuint32 width, vuint32 height)
  : RenderTexture(vikr_PIPELINE_OPENGL, width, height)
{
  m_texture = std::make_unique<GLTexture2D>(width, height);
  m_texture->SetFilterMin(TextureFilterMode::vikr_TEXTURE_LINEAR);
  m_texture->SetFormat(TextureFormat::vikr_RGB);
  m_texture->SetInternalFormat(TextureFormat::vikr_RGB);
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
} // vikr