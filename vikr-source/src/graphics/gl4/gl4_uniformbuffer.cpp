//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_uniformbuffer.hpp>


namespace vikr {


GL4Uniformbuffer::GL4Uniformbuffer()
 : Uniformbuffer(vikr_API_OPENGL)
{
}


vvoid GL4Uniformbuffer::Bind()
{
  glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
}


vvoid GL4Uniformbuffer::Unbind()
{
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


vvoid GL4Uniformbuffer::Generate(vuint32 bind, vuint32 bytes)
{
  if (m_ubo < 0) glGenBuffers(1, &m_ubo);
  Bind();
  /// Start binding to GLSL uniform buffer.
  Unbind();
}
} // vikr