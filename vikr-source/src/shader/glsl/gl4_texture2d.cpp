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
  vint32 channels = 0;
  vbyte *bytecode = Texture::CreateImageByteCode(m_path, &m_width, &m_height, &channels, m_alpha);

  if (m_multisampled) {
    native_target = GetNativeTextureTarget(vikr_TARGET_2D_MULTISAMPLE);
  } else {
    native_target = GetNativeTextureTarget(vikr_TARGET_2D);
  }
  SetPixelStore();
  glGenTextures(1, &id);
  Bind();
  if (m_multisampled) {
    glTexImage2DMultisample(native_target, 4, native_internal_format, m_width, m_height, GL_TRUE);
  } else {
    glTexImage2D(native_target, 0, native_internal_format, m_width, m_height, 0, native_format, native_datatype, bytecode);
    VIKR_ASSERT(glGetError() == 0);
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

  Texture::FreeImageByteCode(bytecode);
  return 1;
}
} // vikr
