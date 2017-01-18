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
  virtual Viewport &GetViewport() = 0;
  virtual vvoid SetViewport(Viewport viewport) = 0;
  virtual glm::vec3 GetClearColor() = 0;
  virtual vvoid AddRenderTarget(RenderTarget *target) = 0;
  virtual vvoid RemoveRenderTarget(vuint32 attachment) = 0;
  virtual Renderbuffer *GetRenderbuffer() = 0;
  virtual Framebuffer *GetFramebuffer() = 0;
  virtual vvoid SetRenderbuffer(Renderbuffer *renderbuffer) = 0;
  virtual vvoid SetClearColor(glm::vec3 color) = 0;
  virtual vvoid SetFramebuffer(Framebuffer *framebuffer) = 0;
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP