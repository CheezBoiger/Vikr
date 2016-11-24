// 
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GLTEXTURE_HPP
#define __VIKR_GLTEXTURE_HPP

#include <shader/texture.hpp>


namespace vikr {


GLenum GetWrapMode(TextureWrapMode mode);
GLenum GetFilterMode(TextureFilterMode mode);
GLenum GetTextureTarget(TextureTarget target);


class GLTexture {
public:
  GLTexture();

protected:

  vuint32 native_format               = GL_RGBA;
  vuint32 native_internal_format      = GL_RGBA;
  vuint32 native_filter_min           = GL_LINEAR;
  vuint32 native_filter_max           = GL_LINEAR_MIPMAP_LINEAR;
};
} // vikr
#endif // __VIKR_GLTEXTURE_HPP