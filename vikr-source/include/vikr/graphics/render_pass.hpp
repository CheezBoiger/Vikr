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
  are what render within a framebuffer for offscreen rendering.

  TODO(): RenderPass Needs to hold ONLY Attachments References, used by the Framebuffer
          to determine which Textures (Images) attach to where (color, depth, stencil, etc).
*/
class RenderPass : public GUID {
public:
  /**
    Polymorphic Renderpass destructor.
  */
  virtual ~RenderPass() { }

  /**
    Add a render target. Returns true if the render target
    successfully attaches. Returns false if rendertarget failed to attach.
  */
  virtual vbool AddRenderTarget(RenderTarget target, vuint32 attachment) = 0;

  /**
    Remove a render target.
  */
  virtual vbool RemoveRenderTarget(vuint32 attachment) = 0;

  /**
    Get a render target from this renderpass. null returned if no attachment by that name.
  */
  virtual RenderTarget *GetRenderTarget(vuint32 attachment) = 0;

  /**
    Number of rendertargets in this RenderPass.
  */
  virtual vuint32 GetNumOfRenderTargets() = 0;
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP