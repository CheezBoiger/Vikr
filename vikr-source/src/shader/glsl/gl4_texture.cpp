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


GLenum GL4Texture::GetBaseFormat(ImageFormat format) {
  switch (format) {
    case vikr_FORMAT_R32_SFLOAT:
    case vikr_FORMAT_R16_SFLOAT:
    case vikr_FORMAT_R8_SNORM: //return GL_RED;
    case vikr_FORMAT_R8_SINT:
    case vikr_FORMAT_R8_UINT:
    case vikr_FORMAT_R8_UNORM:
    case vikr_FORMAT_R16_SINT:
    case vikr_FORMAT_R16_UINT:
    case vikr_FORMAT_R32_SINT: 
    case vikr_FORMAT_R32_UINT: return GL_RED;//return GL_RED_INTEGER;
    case vikr_FORMAT_R8G8B8_SINT:
    case vikr_FORMAT_R8G8B8_UINT:
    case vikr_FORMAT_R32G32B32_UINT:
    case vikr_FORMAT_R16G16B16_SINT:
    case vikr_FORMAT_R16G16B16_UINT: //return GL_RGB_INTEGER;
    case vikr_FORMAT_R16G16B16_SFLOAT:
    case vikr_FORMAT_R32G32B32_SFLOAT: return GL_RGB;
    case vikr_FORMAT_R8G8B8A8_SINT:
    case vikr_FORMAT_R8G8B8A8_UINT: 
    case vikr_FORMAT_R16G16B16A16_SINT:
    case vikr_FORMAT_R16G16B16A16_UINT:
    case vikr_FORMAT_R32G32B32A32_SINT:
    case vikr_FORMAT_R32G32B32A32_UINT: //return GL_RGBA_INTEGER;
    case vikr_FORMAT_R8G8B8A8_UNORM:
    case vikr_FORMAT_R8G8B8A8_SNORM:
    case vikr_FORMAT_R16G16B16A16_SFLOAT:
    case vikr_FORMAT_R32G32B32A32_SFLOAT: return GL_RGBA;
    case vikr_FORMAT_D16_UNORM:
    case vikr_FORMAT_D32_SFLOAT: return GL_DEPTH_COMPONENT;
    //case vikr_FORMAT_D32_SFLOAT: return GL_DEPTH_COMPONENT32F;
    default: return GL_RGBA;
  }  
}


GLenum GL4Texture::GetInternalFormat(ImageFormat format) {
  switch (format) {

    case vikr_FORMAT_R8_SINT: //return GL_R8I;
    case vikr_FORMAT_R8_UINT: //return GL_R8UI;
    case vikr_FORMAT_R8_UNORM: // NO UNORM
    case vikr_FORMAT_R8_SNORM: return GL_R8;//return GL_R8_SNORM;
    case vikr_FORMAT_R16_SFLOAT: //return GL_R16F;
    case vikr_FORMAT_R16_SINT: //return GL_R16I;
    case vikr_FORMAT_R16_UINT:  return GL_R16;//return GL_R16UI;
    case vikr_FORMAT_R32_SFLOAT: //return GL_R32F;
    case vikr_FORMAT_R32_SINT: //return GL_R32I;
    case vikr_FORMAT_R32_UINT: return GL_RED;//return GL_R32UI;
    case vikr_FORMAT_R16G16B16_SFLOAT: return GL_RGB16F;
    case vikr_FORMAT_R8G8B8_SINT: //return GL_RGB8I;
    case vikr_FORMAT_R8G8B8_UINT: return GL_RGB8;//return GL_RGB8UI;
    case vikr_FORMAT_R16G16B16_SINT: //return GL_RGB16I;
    case vikr_FORMAT_R16G16B16_UINT: return GL_RGB16;//return GL_RGB16UI;
    case vikr_FORMAT_R32G32B32_UINT: //return GL_RGBA32UI;
    case vikr_FORMAT_R32G32B32_SINT:
    case vikr_FORMAT_R32G32B32_SFLOAT: return GL_RGB;//return GL_RGB32F;
    case vikr_FORMAT_R8G8B8A8_SINT: //return GL_RGBA8I;
    case vikr_FORMAT_R8G8B8A8_UINT: //return GL_RGBA8UI;
    case vikr_FORMAT_R8G8B8A8_UNORM: // NO UNORM
    case vikr_FORMAT_R8G8B8A8_SNORM: //return GL_RGBA8_SNORM;
    case vikr_FORMAT_R16G16B16A16_SFLOAT: //return GL_RGBA16F;
    case vikr_FORMAT_R16G16B16A16_SINT: //return GL_RGBA16I;
    case vikr_FORMAT_R16G16B16A16_UINT: //return GL_RGBA16UI;
    case vikr_FORMAT_R32G32B32A32_SINT: //return GL_RGBA32I;
    case vikr_FORMAT_R32G32B32A32_UINT: return GL_RGBA;//return GL_RGBA32UI;
    case vikr_FORMAT_R32G32B32A32_SFLOAT: return GL_RGBA32F;
    case vikr_FORMAT_D16_UNORM: //return GL_DEPTH_COMPONENT16;
    case vikr_FORMAT_D32_SFLOAT: return GL_DEPTH_COMPONENT;
    //case vikr_FORMAT_D32_SFLOAT: return GL_DEPTH_COMPONENT32F;
    default: return GL_RGBA;
  }
}


GLenum GL4Texture::GetNativeDataTypeFormat(ImageFormat format) {
  switch (format) {

  case vikr_FORMAT_R8_UINT:
  case vikr_FORMAT_R16_UINT:
  case vikr_FORMAT_R8G8B8_UINT:
  case vikr_FORMAT_R8G8B8A8_UINT: return GL_UNSIGNED_BYTE;
  case vikr_FORMAT_R8_SINT:
  case vikr_FORMAT_R8G8B8_SINT:
  case vikr_FORMAT_R8G8B8A8_SINT: return GL_BYTE;
  case vikr_FORMAT_R16_SINT: 
  case vikr_FORMAT_R16G16B16_SINT: 
  case vikr_FORMAT_R16G16B16A16_SINT:
  case vikr_FORMAT_R32_SINT:
  case vikr_FORMAT_R32G32B32A32_SINT: return GL_INT;
  case vikr_FORMAT_R16G16B16_UINT:
  case vikr_FORMAT_R16G16B16A16_UINT: return GL_UNSIGNED_SHORT;
  case vikr_FORMAT_R32_UINT:
  case vikr_FORMAT_R32G32B32_UINT:
  case vikr_FORMAT_R32G32B32A32_UINT: return GL_UNSIGNED_INT;
  case vikr_FORMAT_R16_SFLOAT:
  case vikr_FORMAT_R32_SFLOAT:
  case vikr_FORMAT_R16G16B16_SFLOAT:
  case vikr_FORMAT_R32G32B32_SFLOAT:
  case vikr_FORMAT_R16G16B16A16_SFLOAT:
  case vikr_FORMAT_R32G32B32A32_SFLOAT:
  case vikr_FORMAT_D32_SFLOAT: return GL_FLOAT;
  case vikr_FORMAT_R8_SNORM: 
  case vikr_FORMAT_R8G8B8A8_SNORM: return GL_SIGNED_NORMALIZED;
  case vikr_FORMAT_R8_UNORM:
  case vikr_FORMAT_R8G8B8A8_UNORM:
  case vikr_FORMAT_D16_UNORM: return GL_UNSIGNED_NORMALIZED;
  default: return GL_UNSIGNED_BYTE;
  }
}


GL4Texture::GL4Texture()
{
  CleanParams();
}


vvoid GL4Texture::SetFormat(ImageFormat format) {
  m_format = format;
  native_format = GetBaseFormat(format);
  native_internal_format = GetInternalFormat(format);
  native_datatype = GetNativeDataTypeFormat(format);
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
  SetFormat(m_format);
  SetFilterMin(m_filter_min);
  SetFilterMax(m_filter_max);
}


vvoid GL4Texture::SetTarget(TextureTarget target) {
  // should not be able to change the texture target.
}


vvoid GL4Texture::SetPixelStore() 
{
  vint32 align;
  switch (native_datatype) {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE: align = 1; break;
    case GL_SHORT:
    case GL_UNSIGNED_SHORT: align = 2; break;
    case GL_INT:
    case GL_UNSIGNED_INT: 
    case GL_FLOAT: align = 4; break;
    case GL_DOUBLE: align = 8; break;
    default: align = 4;
  }
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
} // vikr