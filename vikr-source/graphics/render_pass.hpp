//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDERPASS_HPP
#define __VIKR_RENDERPASS_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

#include <graphics/render_target.hpp>
#include <graphics/viewport.hpp>

#include <vector>


namespace vikr {


class Framebuffer;


/**
  Controls passes that are sent to the Renderer.
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
  std::vector<RenderTarget *> Rendertargets;
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP