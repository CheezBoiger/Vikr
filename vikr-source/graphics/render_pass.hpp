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
  std::vector<std::unique_ptr<RenderTexture> > RenderTextures;

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
  vvoid UpdateRenderTargets() {
    if (FramebufferObject) {
      FramebufferObject->Bind();
      // Clear up last RenderPass in Framebuffer.
      std::vector<Texture *> *targets = FramebufferObject->GetColorAttachments();
      for (vuint32 i = 0; i < targets->size(); ++i) {
        FramebufferObject->ClearTexture(i);
      }
      // Set up the new RenderPass
      std::vector<std::unique_ptr<RenderTexture> > &render_targets = RenderTextures;
      for (vuint32 i = 0; i < render_targets.size(); ++i) {
        RenderTexture *render_target = render_targets[i].get();
        FramebufferObject->BindTexture(render_target, i);
      }
      FramebufferObject->Validate();
      if (Depthbuffer) {
        FramebufferObject->BindDepthStencilBuffer(Depthbuffer.get());
      }
      if(!FramebufferObject->IsComplete()) {
        VikrLog::DisplayMessage(VIKR_ERROR, "Framebuffer is not complete!");
      }
      FramebufferObject->Unbind();
    }
  }


  vvoid Bind() {
    if (FramebufferObject) {
      FramebufferObject->Bind();
    }
  }

  
  vvoid Unbind() {
    if (FramebufferObject) {
      FramebufferObject->Unbind();
    }
  }
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP