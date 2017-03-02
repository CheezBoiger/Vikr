//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/glsl/gl4_texture.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


GLenum GL4Texture::GetNativeWrapMode(TextureWrapMode mode) {
  switch (mode) {
    case vikr_WRAP_REPEAT: return GL_REPEAT;
    case vikr_WRAP_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
    case vikr_WRAP_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
    case vikr_WRAP_CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
    default: return GL_REPEAT;
  }
}


GLenum GL4Texture::GetNativeFilterMode(TextureFilterMode mode) {
  switch (mode) {
    case vikr_FILTER_NEAREST: return GL_NEAREST;
    case vikr_FILTER_LINEAR: return GL_LINEAR;
    case vikr_FILTER_NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
    case vikr_FILTER_LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
    case vikr_FILTER_LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
    case vikr_FILTER_NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
    default: return GL_LINEAR;
  }
}


GLenum GL4Texture::GetNativeTextureTarget(TextureTarget target) {
  switch (target) {
    case vikr_TARGET_1D: return GL_TEXTURE_1D;
    case vikr_TARGET_2D: return GL_TEXTURE_2D; 
    case vikr_TARGET_2D_MULTISAMPLE: return GL_TEXTURE_2D_MULTISAMPLE;
    case vikr_TARGET_3D: return GL_TEXTURE_3D;
    case vikr_TARGET_CUBEMAP: return GL_TEXTURE_CUBE_MAP;
    case vikr_TARGET_CUBEMAP_POSITIVE_X: return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
    case vikr_TARGET_CUBEMAP_NEGATIVE_X: return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
    case vikr_TARGET_CUBEMAP_POSITIVE_Y: return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
    case vikr_TARGET_CUBEMAP_NEGATIVE_Y: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
    case vikr_TARGET_CUBEMAP_POSITIVE_Z: return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
    case vikr_TARGET_CUBEMAP_NEGATIVE_Z: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
    default:  return GL_TEXTURE_2D;
  }
}


GLenum GL4Texture::GetNativeTextureFormat(TextureFormat format) {
  switch (format) {
    case vikr_FORMAT_RGB: return GL_RGB;
    case vikr_FORMAT_RGBA: return GL_RGBA;
    case vikr_FORMAT_RGB16F: return GL_RGB16F;
    case vikr_FORMAT_RGB32F: return GL_RGB32F;
    case vikr_FORMAT_DEPTH: return GL_DEPTH_COMPONENT;
    case vikr_FORMAT_ALPHA: return GL_ALPHA;
    case vikr_FORMAT_RED: return GL_RED;
    default: return GL_RGBA;
  }  
}


GLenum GL4Texture::GetNativeDataTypeFormat(DataTypeFormat format) {
  switch (format) {
    case vikr_DATATYPE_UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
    case vikr_DATATYPE_UNSIGNED_INT: return GL_UNSIGNED_INT;
    case vikr_DATATYPE_FLOAT: return GL_FLOAT;
    default: return GL_UNSIGNED_BYTE;
  }
}


GL4Texture::GL4Texture()
{
  CleanParams();
}


vvoid GL4Texture::SetFormat(TextureFormat format) {
  m_format = format;
  native_format = GetNativeTextureFormat(m_format);
}


vvoid GL4Texture::SetInternalFormat(TextureFormat format) {
  m_internal_format = format;
  native_internal_format = GetNativeTextureFormat(format);
}


vvoid GL4Texture::SetFilterMin(TextureFilterMode filter) {
  m_filter_min = filter;
  native_filter_min = GetNativeFilterMode(m_filter_min);
}


vvoid GL4Texture::SetFilterMax(TextureFilterMode filter) {
  m_filter_max = filter;
  native_filter_max = GetNativeFilterMode(m_filter_max);
}


vvoid GL4Texture::SetWrapS(TextureWrapMode mode) {
  m_wrap_s = mode;
  native_wrap_s = GetNativeWrapMode(m_wrap_s);
}


vvoid GL4Texture::SetWrapT(TextureWrapMode mode) {
  m_wrap_t = mode;
  native_wrap_t = GetNativeWrapMode(m_wrap_t);
}


vvoid GL4Texture::SetWrapR(TextureWrapMode mode) {
  m_wrap_r = mode;
  native_wrap_r = GetNativeWrapMode(m_wrap_r);
}


vvoid GL4Texture::SetDataTypeFormat(DataTypeFormat format) {
  m_datatype = format;
  native_datatype = GetNativeDataTypeFormat(format);
}


vvoid GL4Texture::Bind(vint32 texture) {
  if (texture >= 0) {
    glActiveTexture(GL_TEXTURE0 + texture);
  }
  glBindTexture(native_target, id);
}


vvoid GL4Texture::Unbind() {
  glBindTexture(native_target, 0);
}


vvoid GL4Texture::CleanParams() {
  SetWrapT(m_wrap_r);
  SetWrapS(m_wrap_s);
  SetWrapR(m_wrap_r);
  SetDataTypeFormat(m_datatype);
  SetFormat(m_format);
  SetInternalFormat(m_internal_format);
  SetFilterMin(m_filter_min);
  SetFilterMax(m_filter_max);
}


vvoid GL4Texture::SetTarget(TextureTarget target) {
  // should not be able to change the texture target.
}
} // vikr