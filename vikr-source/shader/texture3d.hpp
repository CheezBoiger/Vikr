//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE3D_HPP
#define __VIKR_TEXTURE3D_HPP

#include <shader/texture2d.hpp>

namespace vikr {


class Texture3D : public Texture2D {
public:

  virtual vvoid Bind(vint32 id = -1) override = 0;
  virtual vvoid Unbind() override = 0;
  
  virtual vint32 Create(vbyte *bytecode) override = 0;

  vvoid SetDepth(vint32 depth) { m_depth = depth; }
  vuint32 GetDepth() { return m_depth; }

protected:

  Texture3D();
  Texture3D(vuint32 width, vuint32 height, vuint32 depth = 0);

  vuint32 m_depth = 0;
};
} // vikr
#endif // __VIKR_TEXTURE3D_HPP