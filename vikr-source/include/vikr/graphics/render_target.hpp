//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_TARGET_HPP
#define __VIKR_RENDER_TARGET_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/cullmode.hpp>
#include <vikr/graphics/depthmode.hpp>
#include <vikr/graphics/stencildepth.hpp>

#include <vector>
#include <memory>
#include <string>

namespace vikr {


enum RenderTargetType {
  vikr_RENDERTARGET_COLOR,
  vikr_RENDERTARGET_DEPTH
};



/// Render Target for offscreen rendering, or even 
/// post processing. OpenGL Identifies them as textures,
/// yet we have the situation in which Vulkan has us 
/// use the same, but without too much of the overhead
/// that is used by textures in general, therefore RenderTargets
/// are going to be different in this case.
class RenderTarget {
public:
  RenderTarget();

  virtual ~RenderTarget() { }

  virtual RenderTargetType GetTargetType() = 0;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
