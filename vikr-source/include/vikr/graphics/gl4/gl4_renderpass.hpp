//
// Copyright (c) Mario Garcia, under the MIT License.
//
#ifndef __VIKR_GL4_RENDERPASS_HPP
#define __VIKR_GL4_RENDERPASS_HPP


#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/viewport.hpp>

#include <vikr/graphics/gl4/gl4_rendertarget.hpp>
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>


namespace vikr {


/**
  RenderPass for OpenGL.
*/
class GL4RenderPass : public RenderPass {
public:

  vvoid UpdateRenderTargets() override;

  vvoid Bind() override;

  vvoid Unbind() override;

  Viewport &GetViewport() override { return m_viewport; }
  vvoid SetViewport(Viewport viewport) override { m_viewport = viewport; }

  glm::vec3 GetClearColor() override { return m_clearcolor; }
  
  vvoid AddRenderTarget(RenderTarget *target) override;
  
  vvoid RemoveRenderTarget(vuint32 attachment) override;
  
  Renderbuffer *GetRenderbuffer() override { return static_cast<Renderbuffer *>(m_renderbuffer); }
  
  Framebuffer *GetFramebuffer() override { return static_cast<Framebuffer *>(m_framebuffer); }
  
  vvoid SetRenderbuffer(Renderbuffer *renderbuffer) override { 
    m_renderbuffer = static_cast<GL4Renderbuffer *>(renderbuffer); 
  } 
  
  vvoid SetClearColor(glm::vec3 color) override { m_clearcolor = color; }
   
  vvoid SetFramebuffer(Framebuffer *framebuffer) override {
    m_framebuffer = static_cast<GL4Framebuffer *>(framebuffer);
  }
private:

  Viewport m_viewport;
  glm::vec3 m_clearcolor;
  GL4Renderbuffer *m_renderbuffer = nullptr;
  GL4Framebuffer *m_framebuffer = nullptr;
  std::vector<RenderTarget *> m_rendertargets;
};
} // vikr
#endif // __VIKR_GL4_RENDERPASS_HPP