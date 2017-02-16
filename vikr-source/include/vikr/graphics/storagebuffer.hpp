//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SHADER_STORAGEBUFFER_HPP
#define __VIKR_SHADER_STORAGEBUFFER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>


namespace vikr {


class ShaderStoragebuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(ShaderStoragebuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(ShaderStoragebuffer);
  ShaderStoragebuffer();

  virtual ~ShaderStoragebuffer() { }


  
};
} // vikr
#endif // _VIKR_SHADER_STORAGEBUFFER_HPP