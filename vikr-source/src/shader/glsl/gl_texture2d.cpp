//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/glsl/gl_texture2d.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


GLTexture2D::GLTexture2D()
{
}


GLTexture2D::GLTexture2D(vuint32 width, vuint32 height) 
{
  m_width = width;
  m_height = height;
}


vint32 GLTexture2D::Create(vbyte *bytecode) {
  m_target = vikr_TEXTURE_2D;
  native_target = GetNativeTextureTarget(m_target);
  glGenTextures(1, &id);
  Bind();
  glTexImage2D(native_target, 0, native_internal_format, m_width, m_height, 0, native_format, native_datatype, bytecode);
  glTexParameteri(native_target, GL_TEXTURE_MIN_FILTER, native_filter_min);
  glTexParameteri(native_target, GL_TEXTURE_MAG_FILTER, native_filter_max);
  glTexParameteri(native_target, GL_TEXTURE_WRAP_S, native_wrap_s);
  glTexParameteri(native_target, GL_TEXTURE_WRAP_T, native_wrap_t);
  if (m_mipmapping) {
    glGenerateMipmap(native_target);
  }
  Unbind();
  return 1;
}
} // vikr
