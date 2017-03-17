//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_TARGET_HPP
#define __VIKR_RENDER_TARGET_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/cullmode.hpp>
#include <vikr/graphics/depthmode.hpp>
#include <vikr/graphics/stencildepth.hpp>
#include <vikr/shader/texture_config.hpp>
#include <vector>
#include <memory>
#include <string>

namespace vikr {


enum RenderTargetType {
  vikr_RENDERTARGET_COLOR,
  vikr_RENDERTARGET_DEPTH,
  vikr_RENDERTARGET_DEPTHSTENCIL
};



/// Render Target for offscreen rendering, or even 
/// post processing. OpenGL Identifies them as textures,
/// yet we have the situation in which Vulkan has us 
/// use the same, but without too much of the overhead
/// that is used by textures in general, therefore RenderTargets
/// are going to be different in this case.
class RenderTarget {
  //VIKR_DISALLOW_COPY_AND_ASSIGN(RenderTarget);
public:
  RenderTarget(RenderTargetType type)
    : m_renderTargetType(type) { }

  virtual ~RenderTarget() { }
  
  /// Set the Image format for this RenderTarget. The Image Format
  /// determines sRGB or depth formats used to determine data
  /// precision for this image.
  virtual vvoid SetFormat(ImageFormat format) = 0;

  /// Get the Image format being used by this render target.
  /// This will determine the precision of this render target,
  /// as well as the type (color, depth...).
  virtual ImageFormat GetFormat() = 0;

  /// Generate the Rendertarget and finalize it's parameters.
  /// Be sure to set the width and height, along with the image format,
  /// before calling this function.
  virtual vvoid Finalize() = 0;

  /// Get the Width, in pixels, of this render target image.
  virtual vuint32 GetWidth() = 0;

  /// Get the Height, in pixels, of this render target image.
  virtual vuint32 GetHeight() = 0;

  /// Set the width of this render target.
  virtual vvoid SetWidth(vuint32 width) = 0;

  /// Set the height of this render target.
  virtual vvoid SetHeight(vuint32 height) = 0;

  /// Get the RenderTarget Type, which can either be a 
  /// color attachment, or a depth attachment. There is also a 
  /// Depth stencil attachment that may also occur is so.
  RenderTargetType GetRenderTargetType() { return m_renderTargetType; }

private:
  /// This variable must not be touched by anyone, as it is 
  /// const.
  const RenderTargetType m_renderTargetType;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
