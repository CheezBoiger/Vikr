//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/glsl/gl_texture1d.hpp>
#include <vikr/shader/glsl/gl_texture.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


GLTexture1D::GLTexture1D()
{
}


GLTexture1D::GLTexture1D(vuint32 width)
{
  m_width = width;
}


vint32 GLTexture1D::Create(vbyte *bytecode) {
  m_target = vikr_TEXTURE_1D;
  native_target = GetNativeTextureTarget(m_target);
  glGenTextures(1, &id);
  Bind();
  glTexImage1D(native_target, 0, native_internal_format, m_width, 0, native_format, native_datatype, bytecode);
  glTexParameteri(native_target, GL_TEXTURE_MIN_FILTER, native_filter_min);
  glTexParameteri(native_target, GL_TEXTURE_MAG_FILTER, native_filter_max);
  glTexParameteri(native_target, GL_TEXTURE_WRAP_S, native_wrap_s);
  if (m_mipmapping) {
    glGenerateMipmap(native_target);
  }
  Unbind();
  return 1;
}
} // vikr