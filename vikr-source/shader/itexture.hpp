//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_ITEXTURE_HPP
#define __VIKR_ITEXTURE_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

namespace vikr {


class ITexture {
public:
  virtual ~ITexture() { }

  virtual vuint32 GetId() = 0;
  virtual vint32 GetWidth() = 0;
  virtual vint32 GetHeight() = 0;
  virtual vbool ContainsAlpha() = 0;
private:
  
};
} // vikr
#endif // __VIKR_ITEXTURE_HPP