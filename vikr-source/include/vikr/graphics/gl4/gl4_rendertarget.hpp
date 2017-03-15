//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GL4_RENDERTARGET_HPP
#define __VIKR_GL4_RENDERTARGET_HPP


#include <vikr/graphics/render_target.hpp>
#include <vikr/graphics/graphics.hpp>


namespace vikr {


class GL4RenderTarget : public RenderTarget {
public:
  

  GLuint GetNativeId() { return target_id; }
private:
  GLuint target_id;  
};
} // vikr
#endif // __VIKR_GL4_RENDERTARGET_HPP