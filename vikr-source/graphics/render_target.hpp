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
  /*
    TODO(Garcia): Redesign RenderTargets to NOT bind to 
    a Frame buffer object until we reach our RenderPasses.
  */
public:
  RenderTarget();
  RenderTarget(vuint32 width, vuint32 height);
  virtual ~RenderTarget();

  virtual vvoid Generate() = 0;

  virtual vvoid BindDepthStencil() = 0;

  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }

  vbool HasDepthAndStencil() { return m_depthstencil; }

  Texture *GetTexture() { return m_texture.get(); }

  GraphicsPipeline GetGraphics() { return pipeline; }
  RenderTargetType GetRenderType() { return m_targetType; }

protected:

  std::unique_ptr<Texture> m_texture        = nullptr;
  vuint32 m_width                           = 0;
  vuint32 m_height                          = 0;  
  vbool m_depthstencil                      = false;

  GraphicsPipeline pipeline;
  RenderTargetType m_targetType             = render_TEXTURE;
};


class RenderBuffer : public RenderTarget {
public:

private:
  vuint32 m_rbo       = 0;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
