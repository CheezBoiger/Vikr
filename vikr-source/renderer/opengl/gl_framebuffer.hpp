//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL_FRAMEBUFFER_HPP
#define __VIKR_GL_FRAMEBUFFER_HPP


#include <renderer/framebuffer.hpp>


namespace vikr {


/**
  GL framebuffer.
*/
class GLFramebuffer : public Framebuffer {
public:
  GLFramebuffer();

  vvoid Generate() override;
  vvoid BindDepthStencil() override;
  vvoid BindTexture(RenderTarget *target, vuint32 index) override;

  vint32 IsComplete() override;

  vvoid Bind() override;
  vvoid Unbind() override;

private:
  
};
} // vikr

#endif // __VIKR_GL_FRAMEBUFFER_HPP