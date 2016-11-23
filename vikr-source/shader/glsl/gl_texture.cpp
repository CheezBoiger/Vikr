//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/gl_texture.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


GLenum GetWrapMode(TextureWrapMode mode) {
  switch (mode) {
    case vikr_TEXTURE_REPEAT: return GL_REPEAT;
    case vikr_TEXTURE_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
    case vikr_TEXTURE_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
    case vikr_TEXTURE_CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
    default: return GL_REPEAT;
  }
}


GLenum GetFilterMode(TextureFilterMode mode) {
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


GLenum GetTextureTarget(TextureTarget target) {
  switch (target) {
    case vikr_TEXTURE_2D: return GL_TEXTURE_2D; 
    case vikr_TEXTURE_3D: return GL_TEXTURE_3D;
    case vikr_TEXTURE_CUBEMAP: return GL_TEXTURE_CUBE_MAP;
    default:  return GL_TEXTURE_2D;
  }
}


GLenum GetTextureFormat(TextureFormat format) {
  switch (format) {
    case vikr_RGB: return GL_RGB;
    case vikr_RGBA: return GL_RGBA;
    default: return GL_RGBA;
  }  
}
} // vikr