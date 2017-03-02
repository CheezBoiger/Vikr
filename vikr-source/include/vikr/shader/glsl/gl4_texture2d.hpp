//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE2D_HPP
#define __VIKR_GL_TEXTURE2D_HPP

#include <vikr/shader/glsl/gl4_texture1d.hpp>

namespace vikr {


class GL4Texture2D : public GL4Texture1D {
public:
  GL4Texture2D(vuint32 width, vuint32 height = 0);
  GL4Texture2D();
  
  virtual vint32 Finalize() override;

  vint32 GetHeight() override { return m_height; }
  vvoid SetHeight(vint32 height) override { m_height = height; }

  virtual vint32 GetDepth() override { return -1; }
  virtual vvoid SetDepth(vint32 depth) override { }

protected:

  vint32 m_height = 0;

};
} // vikr
#endif // __VIKR_GL_TEXTURE2D_HPP