//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE1D_HPP
#define __VIKR_GL_TEXTURE1D_HPP


#include <shader/glsl/gl_texture.hpp>


namespace vikr {


class GLTexture1D : public GLTexture {
public:
  GLTexture1D();
  GLTexture1D(vuint32 width);

  virtual vint32 Create(vbyte *bytecode) override;

};
} // vikr
#endif // __VIKR_GL_TEXTURE1D_HPP