//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/gbuffer.hpp>
#include <vikr/input/window.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/shader/shader_program.hpp>
#include <vikr/graphics/graphics_pipeline_state.hpp>

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
  
  m_rendertargets[0] = device->CreateTexture("gPosition", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[0]->SetWidth(window->GetWidth());
  m_rendertargets[0]->SetHeight(window->GetHeight());
  m_rendertargets[0]->SetMipmapping(false);
  m_rendertargets[0]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[0]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[0]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[0]->SetByteCode(nullptr);
  m_rendertargets[0]->Finalize();

  m_rendertargets[1] = device->CreateTexture("gNormal", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[1]->SetWidth(window->GetWidth());
  m_rendertargets[1]->SetHeight(window->GetHeight());
  m_rendertargets[1]->SetMipmapping(false);
  m_rendertargets[1]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[1]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[1]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[1]->SetByteCode(nullptr);
  m_rendertargets[1]->Finalize();

  m_rendertargets[2] = device->CreateTexture("gAlbedo", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[2]->SetWidth(window->GetWidth());
  m_rendertargets[2]->SetHeight(window->GetHeight());
  m_rendertargets[2]->SetMipmapping(false);
  m_rendertargets[2]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[2]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[2]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[2]->SetByteCode(nullptr);
  m_rendertargets[2]->Finalize();

  m_rendertargets[3] = device->CreateTexture("gSpecular", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[3]->SetWidth(window->GetWidth());
  m_rendertargets[3]->SetHeight(window->GetHeight());
  m_rendertargets[3]->SetMipmapping(false);
  m_rendertargets[3]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[3]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[3]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[3]->SetByteCode(nullptr);
  m_rendertargets[3]->Finalize();

  m_rendertargets[4] = device->CreateTexture("gAmbient", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[4]->SetWidth(window->GetWidth());
  m_rendertargets[4]->SetHeight(window->GetHeight());
  m_rendertargets[4]->SetMipmapping(false);
  m_rendertargets[4]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[4]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[4]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[4]->SetByteCode(nullptr);
  m_rendertargets[4]->Finalize();

  m_rendertargets[5] = device->CreateTexture("gTangent", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[5]->SetWidth(window->GetWidth());
  m_rendertargets[5]->SetHeight(window->GetHeight());
  m_rendertargets[5]->SetMipmapping(false);
  m_rendertargets[5]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[5]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[5]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[5]->SetByteCode(nullptr);
  m_rendertargets[5]->Finalize();

  m_rendertargets[6] = device->CreateTexture("gBitangent", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[6]->SetWidth(window->GetWidth());
  m_rendertargets[6]->SetHeight(window->GetHeight());
  m_rendertargets[6]->SetMipmapping(false);
  m_rendertargets[6]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[6]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[6]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[6]->SetByteCode(nullptr);
  m_rendertargets[6]->Finalize();

  m_rendertargets[7] = device->CreateTexture("gNorm", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[7]->SetWidth(window->GetWidth());
  m_rendertargets[7]->SetHeight(window->GetHeight());
  m_rendertargets[7]->SetMipmapping(false);
  m_rendertargets[7]->SetFormat(vikr_FORMAT_R16G16B16_SFLOAT);
  m_rendertargets[7]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[7]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[7]->SetByteCode(nullptr);
  m_rendertargets[7]->Finalize();

  m_rendertargets[8] = device->CreateTexture("gDepth", vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_rendertargets[8]->SetWidth(window->GetWidth());
  m_rendertargets[8]->SetHeight(window->GetHeight());
  m_rendertargets[8]->SetMipmapping(false);
  m_rendertargets[8]->SetFormat(vikr_FORMAT_D32_SFLOAT);
  m_rendertargets[8]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[8]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[8]->SetWrapS(vikr_WRAP_REPEAT);
  m_rendertargets[8]->SetWrapT(vikr_WRAP_REPEAT);
  m_rendertargets[8]->Finalize();

  
  for (vuint32 i = 0; i < m_rendertargets.size(); ++i) {
    if (m_rendertargets[i]) {
      m_renderpass->AddRenderTarget(RenderTarget(m_rendertargets[i]), i);
    }
  }
  
  m_framebuffer = device->CreateFramebuffer();
  m_framebuffer->Generate();

  /*
    Gbuffer shader. This needs to NOT be a fixed length.
  */
  Shader *vert = device->CreateShader("vert_gbuffer", vikr_VERTEX_SHADER);
  vert->Compile("../../../libs/shader/GLSL/deferred/gbuffer.vert");
  Shader *frag = device->CreateShader("frag_gbuffer", vikr_PIXEL_SHADER);
  frag->Compile("../../../libs/shader/GLSL/deferred/gbuffer.frag");
  m_prgm = device->CreateShaderProgram();
  m_prgm->LoadShader(vert);
  m_prgm->LoadShader(frag);
  m_prgm->Build();

  /**
    Set the RenderPass.
  */
  m_framebuffer->SetRenderPass(m_renderpass);
  m_framebuffer->SetViewport(viewport);
  m_framebuffer->Update();

  bufferlist = device->CreateCommandbufferList();
}


vvoid GBuffer::ExecutePass(CommandbufferList *buffer) {
  if (m_device) {
    Commandbuffer &command = m_device->CreateCommandbuffer(bufferlist);
    command.BeginRecord();
    command.Clear();
    command.SetFramebuffer(m_framebuffer);
    command.SetShaderProgram(m_prgm);
    command.EndRecord();

    m_device->GetContext()->ExecuteCommands(bufferlist);
    m_device->GetContext()->ExecuteCommands(buffer);
  
    bufferlist->Clear();
  }
}
} // vikr