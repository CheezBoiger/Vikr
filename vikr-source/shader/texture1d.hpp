//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE1D_HPP
#define __VIKR_TEXTURE1D_HPP

#include <shader/texture.hpp>

namespace vikr {


/**
  1D texture abstraction.
*/
class Texture1D : public Texture {
public:
  
  virtual vvoid Bind(vint32 id = -1) override = 0;
  virtual vvoid Unbind() override = 0;

  virtual vint32 Create(vbyte *bytecode) override = 0;

  virtual vvoid SetFormat(TextureFormat format) override = 0;
  virtual vvoid SetInternalFormat(TextureFormat format) override = 0;
  virtual vvoid SetFilterMin(TextureFilterMode filter) override = 0;
  virtual vvoid SetFilterMax(TextureFilterMode filter) override = 0;
  virtual vvoid SetWrapS(TextureWrapMode mode) override = 0;
  virtual vvoid SetWrapT(TextureWrapMode mode) override = 0;
  virtual vvoid SetWrapR(TextureWrapMode mode) override = 0;

protected:

  Texture1D();
  Texture1D(vuint32 width);
};
} // vikr
#endif // __VIKR_TEXTURE1D_HPP