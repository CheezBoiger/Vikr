//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDERPASS_HPP
#define __VIKR_RENDERPASS_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <graphics/framebuffer.hpp>
#include <graphics/render_target.hpp>
#include <graphics/viewport.hpp>
#include <util/vikr_log.hpp>

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
    The Given viewport for the RenderPass.
  */
  Viewport                    Viewport;

  /**
    Render target textures and/or depthstencil buffers.
  */
  std::vector<std::unique_ptr<RenderTarget> > RenderTargets;

  /**
    
  */
  std::unique_ptr<Renderbuffer> Depthbuffer;
  /**
    Clear color.
  */
  glm::vec3 ClearColor;

  /**
    FBO
  */
  std::unique_ptr<Framebuffer> FramebufferObject;


  /**
    Update the RenderTargets
  */
  virtual vvoid UpdateRenderTargets() = 0;

  virtual vvoid Bind() = 0;
  
  virtual vvoid Unbind() = 0;
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP