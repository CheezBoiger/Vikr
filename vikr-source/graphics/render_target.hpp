//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_TARGET_HPP
#define __VIKR_RENDER_TARGET_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <graphics/framebuffer.hpp>
#include <shader/texture.hpp>
#include <graphics/blendmode.hpp>
#include <graphics/cullmode.hpp>
#include <graphics/depthmode.hpp>
#include <graphics/stencildepth.hpp>

#include <vector>
#include <memory>

namespace vikr {


enum RenderTargetType {
  render_RENDERBUFFER,
  render_TEXTURE
};


/**
  Render Target for post processing. This is an abstract class
  designed as a plugin for rendering APIs. 

  OpenGL: Associates this object with GLRenderTarget.
  Vulkan: Associates this obejct with VKRenderTarget.
*/
class RenderTarget {
  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderTarget);
  /*
    TODO(Garcia): Redesign RenderTargets to NOT bind to 
    a Frame buffer object until we reach our RenderPasses.
  */
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(RenderTarget);
  RenderTarget(GraphicsPipeline pipeline, 
    vuint32 width,
    vuint32 height,
    vbool alpha = false,
    RenderTargetType type = render_TEXTURE);
  virtual ~RenderTarget() { }

  GraphicsPipeline GetPipeline() { return m_pipeline; }
  RenderTargetType GetRenderType() { return m_targetType; }

  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }

  vvoid SetWidth(vuint32 width) { m_width = width; }
  vvoid SetHeight(vuint32 height) { m_height = height; }

  vbool HasDepthAndStencil() { return m_depthstencil; }

protected:

  vuint32 m_width = 0;
  vuint32 m_height = 0;
  vbool alpha      = false;
  vbool m_depthstencil = false;

  GraphicsPipeline m_pipeline;
  RenderTargetType m_targetType = render_TEXTURE;
};


/**
  RenderTexture.
*/
class RenderTexture : public RenderTarget {
public:
  virtual ~RenderTexture() { }
  RenderTexture(GraphicsPipeline pipeline, vuint32 width, vuint32 height, vbool alpha);

  Texture *GetTexture() { return m_texture.get(); }

protected:

  std::unique_ptr<Texture> m_texture = nullptr;


};


/**
  RenderBuffer.
*/
class Renderbuffer : public RenderTarget {
public:
  virtual ~Renderbuffer() { }
  Renderbuffer(GraphicsPipeline pipeline, vuint32 width, vuint32 height);

  vuint32 GetRenderbufferId() { return m_rbo; }
  
protected:
  vuint32 m_rbo       = 0;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
