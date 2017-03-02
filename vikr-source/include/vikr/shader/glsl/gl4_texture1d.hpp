//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE1D_HPP
#define __VIKR_GL_TEXTURE1D_HPP


#include <vikr/shader/glsl/gl4_texture.hpp>


namespace vikr {


class GL4Texture1D : public GL4Texture {
public:
  GL4Texture1D();
  GL4Texture1D(vuint32 width);

  virtual vint32 GetHeight() override { return -1; }
  virtual vint32 GetDepth() override { return -1; }
  virtual vvoid SetHeight(vint32 height) override { }
  virtual vvoid SetDepth(vint32 depth) override { }

  virtual vint32 Finalize() override;

};
} // vikr
#endif // __VIKR_GL_TEXTURE1D_HPP