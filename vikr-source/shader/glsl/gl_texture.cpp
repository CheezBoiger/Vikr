//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/gl_texture.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


GLenum GLTexture::GetNativeWrapMode(TextureWrapMode mode) {
  switch (mode) {
    case vikr_TEXTURE_REPEAT: return GL_REPEAT;
    case vikr_TEXTURE_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
    case vikr_TEXTURE_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
    case vikr_TEXTURE_CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
    default: return GL_REPEAT;
  }
}


GLenum GLTexture::GetNativeFilterMode(TextureFilterMode mode) {
  switch (mode) {
    case vikr_TEXTURE_NEAREST: return GL_NEAREST;
    case vikr_TEXTURE_LINEAR: return GL_LINEAR;
    case vikr_TEXTURE_NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
    case vikr_TEXTURE_LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
    case vikr_TEXTURE_LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
    case vikr_TEXTURE_NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
    default: return GL_LINEAR;
  }
}


GLenum GLTexture::GetNativeTextureTarget(TextureTarget target) {
  switch (target) {
    case vikr_TEXTURE_1D: return GL_TEXTURE_1D;
    case vikr_TEXTURE_2D: return GL_TEXTURE_2D; 
    case vikr_TEXTURE_3D: return GL_TEXTURE_3D;
    case vikr_TEXTURE_CUBEMAP: return GL_TEXTURE_CUBE_MAP;
    default:  return GL_TEXTURE_2D;
  }
}


GLenum GLTexture::GetNativeTextureFormat(TextureFormat format) {
  switch (format) {
    case vikr_RGB: return GL_RGB;
    case vikr_RGBA: return GL_RGBA;
    default: return GL_RGBA;
  }  
}


GLTexture::GLTexture()
{
}


vvoid GLTexture::SetFormat(TextureFormat format) {
  m_format = format;
  native_format = GetNativeTextureFormat(m_format);
}


vvoid GLTexture::SetInternalFormat(TextureFormat format) {
  m_internal_format = format;
  native_internal_format = GetNativeTextureFormat(format);
}


vvoid GLTexture::SetFilterMin(TextureFilterMode filter) {
  m_filter_min = filter;
  native_filter_min = GetNativeFilterMode(m_filter_min);
}


vvoid GLTexture::SetFilterMax(TextureFilterMode filter) {
  m_filter_max = filter;
  native_filter_max = GetNativeFilterMode(m_filter_max);
}


vvoid GLTexture::SetWrapS(TextureWrapMode mode) {
  m_wrap_s = mode;
  native_wrap_s = GetNativeWrapMode(m_wrap_s);
}


vvoid GLTexture::SetWrapT(TextureWrapMode mode) {
  m_wrap_t = mode;
  native_wrap_t = GetNativeWrapMode(m_wrap_t);
}


vvoid GLTexture::SetWrapR(TextureWrapMode mode) {
  m_wrap_r = mode;
  native_wrap_r = GetNativeWrapMode(m_wrap_r);
}


vvoid GLTexture::Bind(vint32 texture) {
  if (texture >= 0) {
    glActiveTexture(GL_TEXTURE0 + texture);
  }
  glBindTexture(native_target, id);
}


vvoid GLTexture::Unbind() {
  glBindTexture(native_target, 0);
}
} // vikr