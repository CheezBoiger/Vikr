//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/gbuffer.hpp>
#include <vikr/input/window.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/shader/shader_program.hpp>
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
  m_renderpass->SetRenderbuffer(m_renderbuffer.get());

  /*
    Gbuffer shader. This needs to NOT be a fixed length.
  */
  ResourceManager *manager = device->GetResourceManager();
  Shader *vert = manager->CreateShader("vert_gbuffer", VERTEX_SHADER);
  vert->Compile("../../libs/shader/GLSL/gbuffer.vert");
  Shader *frag = manager->CreateShader("frag_gbuffer", PIXEL_SHADER);
  frag->Compile("../../libs/shader/GLSL/gbuffer.frag");
  m_prgm = manager->CreateShaderProgram();
  m_prgm->LoadShader(vert);
  m_prgm->LoadShader(frag);
  m_prgm->Build();

  /**
    Set the RenderPass.
  */
  m_framebuffer->SetRenderPass(m_renderpass.get());
  m_framebuffer->SetViewport(viewport);
  m_framebuffer->Update();
}


vvoid GBuffer::ExecutePass(CommandbufferList *buffer) {
  if (m_device) {
    m_device->GetContext()->Clear();
    m_device->GetContext()->SetFramebuffer(m_framebuffer.get());
    m_device->GetContext()->GetPipelineState()->SetShaderProgram(m_prgm);
    m_device->GetContext()->ExecuteCommands(buffer);
  }
}
} // vikr