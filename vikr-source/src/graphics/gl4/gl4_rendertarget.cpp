//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/lighting/light.hpp>
#include <vikr/shader/glsl/gl_texture2d.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {

/*
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
}*/
} // vikr