//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_ISHADER_HPP
#define __VIKR_ISHADER_HPP


#include <platform/vikr_types.hpp>


namespace vikr {


class IShader {
public:
  IShader() { }
  virtual ~IShader() { }

  virtual vvoid Use() = 0;
  virtual vuint32 GetProgram() = 0;
};
} // vikr
#endif // __VIKR_ISHADER_HPP