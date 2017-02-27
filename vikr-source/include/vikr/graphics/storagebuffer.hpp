//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SHADER_STORAGEBUFFER_HPP
#define __VIKR_SHADER_STORAGEBUFFER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>


namespace vikr {


class ShaderStoragebuffer : public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(ShaderStoragebuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(ShaderStoragebuffer);
  ShaderStoragebuffer();

  virtual ~ShaderStoragebuffer() { }


  virtual vvoid DispatchCompute(vuint32 x, vuint32 y, vuint32 z) = 0;
  virtual vvoid DispathComputeIndirect() = 0;
  
};
} // vikr
#endif // _VIKR_SHADER_STORAGEBUFFER_HPP