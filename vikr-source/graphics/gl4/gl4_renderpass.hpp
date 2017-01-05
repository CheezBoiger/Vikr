//
// Copyright (c) Mario Garcia, under the MIT License.
//
#ifndef __VIKR_GL4_RENDERPASS_HPP
#define __VIKR_GL4_RENDERPASS_HPP


#include <graphics/render_pass.hpp>


namespace vikr {


/**
  RenderPass for OpenGL.
*/
class GL4RenderPass : public RenderPass {
public:

  vvoid UpdateRenderTargets() override;

  vvoid Bind() override;

  vvoid Unbind() override;

};
} // vikr
#endif // __VIKR_GL4_RENDERPASS_HPP