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
} // vikr
#endif // __VIKR_GLTEXTURE_HPP