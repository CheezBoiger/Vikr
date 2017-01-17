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
  
  virtual vint32 Create(vbyte *bytecode) override;

  vuint32 GetHeight() { return m_height; }

protected:

  vuint32 m_height = 0;

};
} // vikr
#endif // __VIKR_GL_TEXTURE2D_HPP