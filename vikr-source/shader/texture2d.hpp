//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE2D_HPP
#define __VIKR_TEXTURE2D_HPP

#include <shader/texture1d.hpp>

namespace vikr {


/*
  2D texture abstraction.
*/
class Texture2D : public Texture1D {
public:
  /**
    Bind texture.
  */
  virtual vvoid Bind(vint32 id = -1) override = 0;
  virtual vvoid Unbind() override = 0;

  virtual vint32 Create(vbyte *bytecode) override = 0;

  vvoid SetWidth(vint32 height) { m_height = height; }
  vuint32 GetWidth() { return m_height; }

  
protected:

  Texture2D() 
    : m_height(0) { }

  Texture2D(vuint32 width, vuint32 height = 0) 
    : m_height(height) { m_width = width; }

  vuint32 m_height = 0;
};
} // vikr
#endif // __VIKR_TEXTURE2D_HPP