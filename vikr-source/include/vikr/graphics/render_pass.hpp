//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDERPASS_HPP
#define __VIKR_RENDERPASS_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_target.hpp>
#include <vikr/graphics/viewport.hpp>
#include <vikr/util/vikr_log.hpp>

#include <vector>


namespace vikr {


class Framebuffer;


/**
  Controls passes that are sent to the Renderer. These RenderPasses
  are what render on to the Screen Quad.
  Note: This can be a struct.
*/
class RenderPass {
public:
  /**
    Polymorphic Renderpass destructor.
  */
  virtual ~RenderPass() { }
  /**
    Update the RenderTargets
  */
  virtual vvoid UpdateRenderTargets() = 0;

  /**
    Bind the Renderpass.
  */
  virtual vvoid Bind() = 0;
  
  /**
    Unbind the Renderpass.
  */
  virtual vvoid Unbind() = 0;

  /**
    Get the view port of this Renderpass.
  */
  virtual const Viewport &GetViewport() const = 0;

  /**
    Set the viewport for this Renderpass.
  */
  virtual vvoid SetViewport(Viewport viewport) = 0;

  /**
    Get the color that the graphics context uses to clear the screen with.
  */
  virtual glm::vec3 GetClearColor() const = 0;

  /**
    Add a render target. Returns true if the render target
    successfully attaches. Returns false if rendertarget failed to attach.
  */
  virtual vbool AddRenderTarget(RenderTarget *target, vuint32 attachment) = 0;

  /**
    Remove a render target.
  */
  virtual vbool RemoveRenderTarget(vuint32 attachment) = 0;

  /**
    Get the Renderbuffer, which corresponds to the depth buffer, or depth-stencil buffer.
  */
  virtual Renderbuffer *GetRenderbuffer() const = 0;

  /**
    Get the Framebuffer associated with this RenderPass.
  */
  virtual Framebuffer *GetFramebuffer() const = 0;

  /**
    Set the Renderbuffer for this Renderpass. This can be a Depth buffer, or 
    Depth-Stencil buffer.
  */
  virtual vvoid SetRenderbuffer(Renderbuffer *renderbuffer) = 0;

  /**
    Set the Clear Color for this Renderpass, the color which will be used by the
    graphics context to clear the screen with.
  */
  virtual vvoid SetClearColor(glm::vec3 color) = 0;

  /**
    Set the Framebuffer for this Renderpass. This is the Framebuffer used to 
    Draw into for offscreen rendering.
  */
  virtual vvoid SetFramebuffer(Framebuffer *framebuffer) = 0;
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP