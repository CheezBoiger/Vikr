//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/glsl/gl4_texture2d.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>


namespace vikr {


GL4Texture2D::GL4Texture2D()
{
}


GL4Texture2D::GL4Texture2D(vuint32 width, vuint32 height) 
{
  m_width = width;
  m_height = height;
}


vint32 GL4Texture2D::Finalize() {
  if (m_multisampled) {
    m_target = vikr_TEXTURE_2D_MULTISAMPLE;
  } else {
    m_target = vikr_TEXTURE_2D;
  }
  native_target = GetNativeTextureTarget(m_target);
  glGenTextures(1, &id);
  Bind();
  if (m_multisampled) {
    glTexImage2DMultisample(native_target, 0, native_internal_format, m_width, m_height, GL_TRUE);
  } else {
    glTexImage2D(native_target, 0, native_internal_format, m_width, m_height, 0, native_format, native_datatype, m_bytecode);
    glTexParameteri(native_target, GL_TEXTURE_MIN_FILTER, native_filter_min);
    glTexParameteri(native_target, GL_TEXTURE_MAG_FILTER, native_filter_max);
    glTexParameteri(native_target, GL_TEXTURE_WRAP_S, native_wrap_s);
    glTexParameteri(native_target, GL_TEXTURE_WRAP_T, native_wrap_t);
    if (m_mipmapping) {
      glGenerateMipmap(native_target);
    }
  }
  Unbind();

  VIKR_ASSERT(glGetError() == 0);
  return 1;
}
} // vikr
