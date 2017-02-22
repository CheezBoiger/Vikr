//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE2D_HPP
#define __VIKR_GL_TEXTURE2D_HPP

#include <vikr/shader/glsl/gl_texture1d.hpp>

namespace vikr {


class GLTexture2D : public GLTexture1D {
public:
  GLTexture2D(vuint32 width, vuint32 height = 0);
  GLTexture2D();
  
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