//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_TARGET_HPP
#define __VIKR_RENDER_TARGET_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/framebuffer.hpp>
#include <shader/texture.hpp>
#include <renderer/blendmode.hpp>
#include <renderer/cullmode.hpp>
#include <renderer/depthmode.hpp>
#include <renderer/stencildepth.hpp>

#include <vector>
#include <memory>

namespace vikr {


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

protected:

  vuint32 m_rbo                             = 0;
  std::unique_ptr<Texture> m_texture        = nullptr;
  vuint32 m_width                           = 0;
  vuint32 m_height                          = 0;  
  vbool m_depthstencil                      = false;

  GraphicsPipeline pipeline;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
