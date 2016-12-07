//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDERTARGET_HPP
#define __VIKR_RENDERTARGET_HPP

#include <renderer/render_target.hpp>
#include <renderer/cullmode.hpp>
#include <renderer/depthmode.hpp>
#include <renderer/stencildepth.hpp>
#include <renderer/blendmode.hpp>


namespace vikr {


/**
  OpenGL Implementation of a RenderTarget.
*/
class GLRenderTarget : public RenderTarget {
  static GLenum GetDepthFunct(DepthFunc funct);
  static GLenum GetBlendFunct(BlendFunc blend);
  static GLenum GetCullFace(CullFace face);
  static GLenum GetFrontFace(FrontFace mode);
  static GLenum GetBlendEq(BlendEq eq);
public:

  GLRenderTarget();

  GLRenderTarget(vuint32 width, vuint32 height);

  vvoid Generate() override;

  vvoid BindDepthStencil() override;

  vvoid SetDepthFunc(DepthFunc funct) override;
  vvoid SetBlendSrc(BlendFunc funct) override;
  vvoid SetBlendDst(BlendFunc funct) override;
  vvoid SetCullFace(CullFace face) override;
  vvoid SetFrontFace(FrontFace face) override;
  vvoid SetBlendEq(BlendEq eq) override;


  GLenum GetNativeDepthFunc() { return native_depthFunc; }
  GLenum GetNativeBlendEq() { return native_blendEq; }
  GLenum GetNativeBlendSrc() { return native_blendSrc; }
  GLenum GetNativeBlendDst() { return native_blendDst; }
  GLenum GetNativeCullFace() { return native_cullFace; }
  GLenum GetNativeFrontFace() { return native_frontFace; }

private:

  GLenum native_depthFunc         = 0;
  GLenum native_blendEq           = 0;
  GLenum native_blendSrc          = 0;
  GLenum native_blendDst          = 0;
  GLenum native_cullFace          = 0;
  GLenum native_frontFace         = 0;
 
};
} // vikr
#endif // __VIKR_RENDERTARGET_HPP