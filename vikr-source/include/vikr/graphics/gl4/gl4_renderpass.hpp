//
// Copyright (c) Mario Garcia, under the MIT License.
//
#ifndef __VIKR_GL4_RENDERPASS_HPP
#define __VIKR_GL4_RENDERPASS_HPP


#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/viewport.hpp>

#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>

#include <map>


namespace vikr {


/**
  RenderPass for OpenGL.
*/
class GL4RenderPass : public RenderPass {
public:
  
  /**
    Add a rendertarget, this is most likely going to be a render texture.
  */
  vbool AddRenderTarget(RenderTarget target, vuint32 attachment) override;
  
  /**
    Remove the render target at the attachment point. This is the index that the render
    target was bound to.
  */
  vbool RemoveRenderTarget(vuint32 attachment) override;

  RenderTarget *GetRenderTarget(vuint32 attachment) override;

  /**
  */
  vuint32 GetNumOfRenderTargets() override 
    { return m_rendertargets.size(); }

  /**
    Get the RenderTargets
  */
  std::map<vuint32, RenderTarget> &GetRenderTargets() 
    { return m_rendertargets; }

private:

  /**
    The rendertargets that are weakly referenced.
  */
  std::map<vuint32, RenderTarget> m_rendertargets;
};
} // vikr
#endif // __VIKR_GL4_RENDERPASS_HPP