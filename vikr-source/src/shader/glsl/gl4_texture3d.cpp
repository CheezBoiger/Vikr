//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/shader/glsl/gl4_texture3d.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


GL4Texture3D::GL4Texture3D()
{
}


GL4Texture3D::GL4Texture3D(vuint32 width, vuint32 height, vuint32 depth)
{
  m_width = width;
  m_height = height;
  m_depth = depth;
}


vint32 GL4Texture3D::Finalize() {
  vbyte *bytecode = Texture::CreateImageByteCode(m_path, &m_width, &m_height, &m_depth, m_alpha);
  native_target  = GetNativeTextureTarget(vikr_TARGET_3D);
  SetPixelStore();
  glGenTextures(1, &id);
  Bind();
  glTexImage3D(native_target, 0, native_internal_format, m_width, 
    m_height, m_depth, 0, native_format, native_datatype, bytecode);

  glTexParameteri(native_target, GL_TEXTURE_MIN_FILTER, native_filter_min);
  glTexParameteri(native_target, GL_TEXTURE_MAG_FILTER, native_filter_max);
  glTexParameteri(native_target, GL_TEXTURE_WRAP_S, native_wrap_s);
  glTexParameteri(native_target, GL_TEXTURE_WRAP_T, native_wrap_t);
  glTexParameteri(native_target, GL_TEXTURE_WRAP_R, native_wrap_r);
  if (m_mipmapping) {
    glGenerateMipmap(native_target);
  }
  Unbind();
  Texture::FreeImageByteCode(bytecode);
  return 1;
}
} // vikr