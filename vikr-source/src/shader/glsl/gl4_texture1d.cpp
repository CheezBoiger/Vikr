//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/glsl/gl4_texture1d.hpp>
#include <vikr/shader/glsl/gl4_texture.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


GL4Texture1D::GL4Texture1D()
{
}


GL4Texture1D::GL4Texture1D(vuint32 width)
{
  m_width = width;
}


vint32 GL4Texture1D::Finalize() {
  vint32 h, c;
  vbyte *bytecode = Texture::CreateImageByteCode(m_path, &m_width, &h, &c, m_alpha);
  native_target = GetNativeTextureTarget(vikr_TARGET_1D);
  SetPixelStore();
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
  Texture::FreeImageByteCode(bytecode);
  return 1;
}
} // vikr