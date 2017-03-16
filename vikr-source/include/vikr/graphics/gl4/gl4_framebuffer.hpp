//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GL4_FRAMEBUFFER_HPP
#define __VIKR_GL4_FRAMEBUFFER_HPP


#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/graphics.hpp>

#include <map>


namespace vikr {


class GL4RenderPass;


/// GL4 framebuffer.
///
/// Must call Generate() in order to generate a Framebuffer.
class GL4Framebuffer : public Framebuffer {
  vuint32 GetFramebufferMode(BufferMode mode);
public:
  GL4Framebuffer();

  vvoid Generate() override;

  glm::vec3 GetClearColor() override { return m_clearcolor; }
  vvoid SetClearColor(glm::vec3 color) override { m_clearcolor = color; }

  GLuint GetFramebufferId() { return m_fbo; }
  
  /// Check if the framebuffer is complete.
  vint32 IsComplete() override;

  vvoid Bind();
  vvoid Unbind();

  vvoid ClearAttachments();

  vvoid Update() override;

  vvoid Readbuffer(BufferMode mode) override;
  vvoid Writebuffer(BufferMode mode) override;
  
  vvoid Cleanup() override;


  RenderPass *GetRenderPass() override;
  vvoid SetRenderPass(RenderPass *pass) override;

  Viewport GetViewport() override { return m_viewport; }
  vvoid SetViewport(const Viewport &viewport) override;

  vbool HasDepthStencil() override;
  vbool IsMultisampled() override;

  vvoid BlitTo(Framebuffer *framebuffer) override;

  vvoid InsertNewRenderTarget(RenderTargetType type, vuint32 point) override;
  RenderTarget *GetRenderTarget(vuint32 point) override;
  vbool RemoveRenderTarget(vuint32 point) override;
  vuint32 GetNumOfRenderTargets() override { return rendertargets.size(); }

private:
  /**
    Get the clear color for this framebuffer.
  */
  glm::vec3 m_clearcolor            = glm::vec3(0.1f, 0.1f, 0.1f);
  GLuint m_fbo                     = 0;
  GL4RenderPass *m_renderPass = nullptr;
  Viewport m_viewport;
  GLint m_read;
  GLint m_write;
  std::vector<GL4RenderTarget> rendertargets;
}; 
} // vikr
#endif // __VIKR_