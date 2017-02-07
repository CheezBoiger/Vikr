//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/gbuffer.hpp>
#include <vikr/input/window.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/graphics/pipeline_state.hpp>

namespace vikr {


GBuffer::GBuffer()
{ 
}


vvoid GBuffer::Init(RenderDevice *device) {
  m_device = device;
  Window *window = Window::GetMainWindow();
  m_renderpass = device->CreateRenderPass();
  Viewport viewport;
  viewport.win_x = 0;
  viewport.win_y = 0;
  viewport.win_width = Window::GetMainWindow()->GetWidth();
  viewport.win_height = Window::GetMainWindow()->GetHeight();
  m_renderpass->SetViewport(viewport);
  
  m_rendertargets[0] = device->CreateRenderTexture("gPosition",
    window->GetWidth(), window->GetHeight(), false, false, data_FLOAT);
  m_rendertargets[1] = device->CreateRenderTexture("gNormal",
    window->GetWidth(), window->GetHeight(), true, false, data_UNSIGNED_BYTE);
  m_rendertargets[2] = device->CreateRenderTexture("gAlbedo",
    window->GetWidth(), window->GetHeight(), true, false, data_UNSIGNED_BYTE);
  m_rendertargets[3] = device->CreateRenderTexture("gSpecular",
   window->GetWidth(), window->GetHeight(), true, false, data_UNSIGNED_BYTE);
  m_rendertargets[4] = device->CreateRenderTexture("gAmbient",
   window->GetWidth(), window->GetHeight(), true, false, data_UNSIGNED_BYTE);
  m_rendertargets[5] = device->CreateRenderTexture("gTangent",
   window->GetWidth(), window->GetHeight(), false, false, data_FLOAT);
  m_rendertargets[6] = device->CreateRenderTexture("gBitangent",
   window->GetWidth(), window->GetHeight(), false, false, data_FLOAT);
  m_rendertargets[7] = device->CreateRenderTexture("gNorm",
   window->GetWidth(), window->GetHeight(), false, false, data_FLOAT);
  
  for (vuint32 i = 0; i < m_rendertargets.size(); ++i) {
    if (m_rendertargets[i]) {
      m_renderpass->AddRenderTarget(m_rendertargets[i].get(), i);
    }
  }
  
  m_framebuffer = device->CreateFramebuffer();
  m_framebuffer->Generate();
  m_renderbuffer = device->CreateRenderbuffer(window->GetWidth(), window->GetHeight(), false);
  m_renderpass->SetFramebuffer(m_framebuffer.get());
  m_renderpass->SetRenderbuffer(m_renderbuffer.get());

  /*
    Gbuffer shader. This needs to NOT be a fixed length.
  */
  Shader *vert = device->GetResourceManager()->CreateShader("vert_gbuffer", VERTEX_SHADER);
  vert->Compile("../../libs/shader/GLSL/gbuffer.vert");
  Shader *frag = device->GetResourceManager()->CreateShader("frag_gbuffer", FRAGMENT_SHADER);
  frag->Compile("../../libs/shader/GLSL/gbuffer.frag");
  renderstate = device->GetResourceManager()->CreatePipelineState("gbuffer");
  renderstate->LoadShader(vert);
  renderstate->LoadShader(frag);
  
  m_gbuffershader = device->GetResourceManager()->GetShader("gbuffer");

  m_renderpass->UpdateRenderTargets(); 
}


vvoid GBuffer::ExecutePass(CommandbufferList *buffer) {
  if (m_device) {
    m_device->GetContext()->Clear();
    m_device->GetContext()->SetRenderPass(m_renderpass.get());
    m_device->GetContext()->ApplyShaderProgram(m_gbuffershader);
    m_device->GetContext()->ExecuteCommands(buffer);
  }
}
} // vikr