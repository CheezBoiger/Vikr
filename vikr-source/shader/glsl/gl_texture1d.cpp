//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/gl_texture1d.hpp>
#include <shader/glsl/gl_texture.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


GLTexture1D::GLTexture1D()
  : Texture1D()
{
}


GLTexture1D::GLTexture1D(vuint32 width)
  : Texture1D(width)
{
}


vint32 GLTexture1D::Create(vbyte *bytecode) {
  return 0;
}


vvoid GLTexture1D::SetFormat(TextureFormat format) {
    
}
} // vikr