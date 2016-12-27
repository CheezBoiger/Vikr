//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_renderpass.hpp>

#include <util/vikr_log.hpp>
#include <util/vikr_assert.hpp>


namespace vikr {


vvoid GL4RenderPass::UpdateRenderTargets() {
  if(FramebufferObject) {
    FramebufferObject->Bind();
    // Clear up last RenderPass in Framebuffer.
    std::vector<Texture *> *targets = FramebufferObject->GetColorAttachments();
    for(vuint32 i = 0; i < targets->size(); ++i) {
      FramebufferObject->ClearTexture(i);
    }
    targets->clear();
    // Set up the new RenderPass
    std::vector<std::unique_ptr<RenderTarget> > &render_targets = RenderTargets;
    for(vuint32 i = 0; i < render_targets.size(); ++i) {
      if(render_targets[i]->GetRenderType() == RenderTargetType::render_TEXTURE) {
        FramebufferObject->BindTexture(render_targets[i].get(), i);
      }
    }
    FramebufferObject->Validate();
    if(Depthbuffer) {
      FramebufferObject->BindDepthStencilBuffer(Depthbuffer.get());
    }
    if(!FramebufferObject->IsComplete()) {
      VikrLog::DisplayMessage(VIKR_ERROR, "Framebuffer is not complete!");
    }
    FramebufferObject->Unbind();
  }
}


vvoid GL4RenderPass::Bind() {
  if(FramebufferObject) {
    FramebufferObject->Bind();
  }
}


vvoid GL4RenderPass::Unbind() {
  if(FramebufferObject) {
    FramebufferObject->Unbind();
  }
}
} // vikr