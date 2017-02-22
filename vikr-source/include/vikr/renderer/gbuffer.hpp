//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GBUFFER_HPP
#define __VIKR_GBUFFER_HPP


#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_target.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/shader/shader.hpp>

#include <vikr/graphics/command_buffer.hpp>

#include <memory>
#include <array>


namespace vikr {


const vuint32 GBUFFER_SIZE = 9;
class ShaderProgram;

/**
  Standard G buffer object. Still needs to be fixed.
*/
class GBuffer {
public:
  GBuffer();

  vvoid Init(RenderDevice *device = nullptr);

  vvoid ExecutePass(CommandbufferList *buffer);

  RenderTarget *GetRenderTarget(vuint32 index) {
    return m_renderpass->GetRenderTarget(index);
  }

  vuint32 GetNumOfRenderTargets() { return m_rendertargets.size(); }

  Framebuffer *GetFramebuffer() { return m_framebuffer.get(); }
  RenderPass *GetRenderPass() { return m_renderpass.get(); }

private:
  RenderDevice *m_device = nullptr;
  std::unique_ptr<RenderPass> m_renderpass;
  std::unique_ptr<Framebuffer> m_framebuffer;
  ShaderProgram *m_prgm;
  
  std::array<Texture *, GBUFFER_SIZE> m_rendertargets;
};
} // vikr
#endif // __VIKR_GBUFFER_HPP