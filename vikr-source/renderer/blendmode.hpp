//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_BLENDMODE_HPP
#define __VIKR_BLENDMODE_HPP


namespace vikr {


enum class BlendFunc {
  vikr_BLEND_ZERO,
  vikr_BLEND_ONE,
  vikr_BLEND_SRC_COLOR,
  vikr_BLEND_ONE_MINUS_SRC_COLOR,
  vikr_BLEND_DST_COLOR,
  vikr_BLEND_ONE_MINUS_DST_COLOR,
  vikr_BLEND_SRC_ALPHA,
  vikr_BLEND_ONE_MINUS_SRC_ALPHA,
  vikr_BLEND_DST_ALPHA,
  vikr_BLEND_ONE_MINUS_DST_ALPHA,
  vikr_BLEND_CONSTANT_COLOR,
  vikr_BLEND_ONE_MINUS_CONSTANT_COLOR,
  vikr_BLEND_CONSTANT_ALPHA,
  vikr_BLEND_GL_ONE_MINUS_CONSTANT_ALPHA  
};


enum class BlendEq {
  vikr_BLEND_ADD, // Default
  vikr_BLEND_SUBTRACT,
  vikr_BLEND_REVERSE_SUBTRACT,
};
} // vikr
#endif // __VIKR_BLENDMODE_HPP