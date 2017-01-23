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
    Updates rendertargets into the framebuffer of this Renderpass.
  */
  vvoid UpdateRenderTargets() override;

  /**
    Bind the RenderPass.
  */
  vvoid Bind() override;

  /**
    Unbind the renderpass. Do this after you have bounded it.
  */
  vvoid Unbind() override;

  /**
    Get the viewport of this renderpass.
  */
  const Viewport &GetViewport() const override { return m_viewport; }
  
  /**
    Set the viewport of this renderpass.
  */
  vvoid SetViewport(Viewport viewport) override { m_viewport = viewport; }

  /**
    Get the clear color for which this render pass uses to clear the screen.
  */
  glm::vec3 GetClearColor() const override { return m_clearcolor; }
  
  /**
    Add a rendertarget, this is most likely going to be a render texture.
  */
  vbool AddRenderTarget(RenderTarget *target, vuint32 attachment) override;
  
  /**
    Remove the render target at the attachment point. This is the index that the render
    target was bound to.
  */
  vbool RemoveRenderTarget(vuint32 attachment) override;

  RenderTarget *GetRenderTarget(vuint32 attachment) override;
  
  /**
    Get the Renderbuffer of this renderpass. This is most likely the 
    depth buffer that was set by the user, you will receive back.
  */
  Renderbuffer *GetRenderbuffer() const override 
    { return static_cast<Renderbuffer *>(m_renderbuffer); }
  
  /**
    Get the Framebuffer that the user assigned to this renderpass.
  */
  Framebuffer *GetFramebuffer() const override 
    { return static_cast<Framebuffer *>(m_framebuffer); }
  
  /**
    Set the Renderbuffer for this renderpass.
  */
  vvoid SetRenderbuffer(Renderbuffer *renderbuffer) override { 
    m_renderbuffer = static_cast<GL4Renderbuffer *>(renderbuffer); 
  } 
  
  /**
    Set the clear color of this renderpass.
  */
  vvoid SetClearColor(glm::vec3 color) override { m_clearcolor = color; }
   
  /**
    Set the Framebuffer of this renderpass.
  */
  vvoid SetFramebuffer(Framebuffer *framebuffer) override 
    { m_framebuffer = static_cast<GL4Framebuffer *>(framebuffer); }

private:

  /**
    The viewport of this renderpass.
  */
  Viewport m_viewport;

  /**
    The clear color of this renderpass.
  */
  glm::vec3 m_clearcolor;

  /**
    The weak ref render buffer, most likely the depth buffer of this renderpass.
  */
  GL4Renderbuffer *m_renderbuffer = nullptr;
  /**
    The weak reference of the framebuffer of this renderpass.
  */
  GL4Framebuffer *m_framebuffer = nullptr;

  /**
    The rendertargets that are weakly referenced.
  */
  std::map<vuint32, RenderTarget *> m_rendertargets;
};
} // vikr
#endif // __VIKR_GL4_RENDERPASS_HPP