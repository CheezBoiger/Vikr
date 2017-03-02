//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_TARGET_HPP
#define __VIKR_RENDER_TARGET_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/cullmode.hpp>
#include <vikr/graphics/depthmode.hpp>
#include <vikr/graphics/stencildepth.hpp>

#include <vector>
#include <memory>
#include <string>

namespace vikr {


enum RenderTargetType {
  render_RENDERBUFFER,
  render_TEXTURE,
  render_TEXTURE_MULTISAMPLE,
};


/**
  Render Target for post processing. This is a container for Textures to
  Be added into RenderPasses. 
*/
class RenderTarget {
  /*
    TODO(Garcia): Redesign RenderTargets to NOT bind to 
    a Frame buffer object until we reach our RenderPasses.
  */
public:
  RenderTarget(Texture *texture = nullptr)
    : m_texture(texture) 
  {
    DetermineRenderType();
  }

  ~RenderTarget() { }

  Texture *GetTexture() 
    { return m_texture; }

  vvoid SetTexture(Texture *texture)
    { m_texture = texture; DetermineRenderType(); }

  RenderTargetType GetRenderType()
    { return m_renderType; }

private:

  vvoid DetermineRenderType() {
    if (m_texture) {
      switch (m_texture->GetTargetFormat()) {
        case vikr_TARGET_3D:
        case vikr_TARGET_2D:
        case vikr_TARGET_1D: 
          m_renderType = render_TEXTURE; break;
        case vikr_TARGET_2D_MULTISAMPLE: 
          m_renderType = render_TEXTURE_MULTISAMPLE; break;
        default: 
          m_renderType = render_TEXTURE; break;
      }
    } 
  }
  
  Texture *m_texture = nullptr;
  RenderTargetType m_renderType;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
