//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE1D_HPP
#define __VIKR_GL_TEXTURE1D_HPP


#include <shader/texture1d.hpp>


namespace vikr {


class GLTexture1D : public Texture1D {
public:
  GLTexture1D();
  GLTexture1D(vuint32 width);

  vint32 Create(vbyte *bytecode) override;

  virtual vvoid Bind(vint32 id = -1) override = 0;
  virtual vvoid Unbind() override = 0;
  
  vvoid SetFormat(TextureFormat format) override;
  vvoid SetInternalFormat(TextureFormat format) override;
  vvoid SetFilterMin(TextureFilterMode filter) override;
  vvoid SetFilterMax(TextureFilterMode filter) override;
  vvoid SetWrapS(TextureWrapMode mode) override;
  vvoid SetWrapT(TextureWrapMode mode) override;
  vvoid SetWrapR(TextureWrapMode mode) override;

};
} // vikr
#endif // __VIKR_GL_TEXTURE1D_HPP