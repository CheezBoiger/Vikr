//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE2D_HPP
#define __VIKR_GL_TEXTURE2D_HPP

#include <shader/texture2d.hpp>

namespace vikr {


class GLTexture2D : public Texture2D {
public:
  GLTexture2D(vuint32 width, vuint32 height = 0);
  GLTexture2D();
  
  vvoid Bind(vint32 id = -1) override;
  vvoid Unbind() override;
  
  vint32 Create(vbyte *bytecode) override;

};
} // vikr
#endif // __VIKR_GL_TEXTURE2D_HPP