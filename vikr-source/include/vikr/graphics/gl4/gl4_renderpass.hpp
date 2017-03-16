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



/// RenderPass for OpenGL.
class GL4RenderPass : public RenderPass {
public:
  GL4RenderPass()
    : RenderPass(vikr_API_OPENGL) { }  

  vvoid Generate() override;

private:
};
} // vikr
#endif // __VIKR_GL4_RENDERPASS_HPP