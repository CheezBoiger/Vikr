//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDERPASS_HPP
#define __VIKR_RENDERPASS_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

#include <renderer/render_target.hpp>
#include <renderer/viewport.hpp>

#include <vector>


namespace vikr {


/**
  Controls passes that are sent to the Renderer.
*/
struct RenderPass {
  
  Viewport Viewport;
  std::vector<RenderTarget *> Rendertargets;
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP