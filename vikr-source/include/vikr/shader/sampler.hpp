//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SAMPLER_HPP
#define __VIKR_SAMPLER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/platform.hpp>
#include <vikr/platform/vikr_types.hpp>


namespace vikr {


/// Sampler defines filtering for texture samples
/// that are going to be used in GLSL shaders. they are mainly
/// to reduce the amount of textures that are built in with robust
/// variable types, and instead can be reused for numerous texture bindings
/// rather than one.
class Sampler {
public:
  
  virtual ~Sampler() { }

private:

  
};
} // vikr
#endif // __VIKR_SAMPLER_HPP