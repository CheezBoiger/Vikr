//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDERTARGET_HPP
#define __VIKR_RENDERTARGET_HPP

#include <renderer/render_target.hpp>


namespace vikr {


class GLRenderTarget : public RenderTarget {
public:

  GLRenderTarget();

  GLRenderTarget(vuint32 width, vuint32 height);

  vvoid Generate() override;

  vvoid BindDepthStencil() override;
  vvoid BindTexture(vuint32 index) override;
  
  vvoid Unbind() override;
  vvoid Bind() override;

private:

};
} // vikr
#endif // __VIKR_RENDERTARGET_HPP