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
  ResourceManager *mgr = device->GetResourceManager();
  
  m_rendertargets[0] = mgr->CreateTexture("gPosition", vikr_TARGET_2D, "", false);
  m_rendertargets[0]->SetWidth(window->GetWidth());
  m_rendertargets[0]->SetHeight(window->GetHeight());
  m_rendertargets[0]->SetMipmapping(false);
  m_rendertargets[0]->SetMultisampled(false);
  m_rendertargets[0]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[0]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[0]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[0]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[0]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[0]->SetByteCode(nullptr);
  m_rendertargets[0]->Finalize();

  m_rendertargets[1] = mgr->CreateTexture("gNormal", vikr_TARGET_2D, "", false);
  m_rendertargets[1]->SetWidth(window->GetWidth());
  m_rendertargets[1]->SetHeight(window->GetHeight());
  m_rendertargets[1]->SetMipmapping(false);
  m_rendertargets[1]->SetMultisampled(false);
  m_rendertargets[1]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[1]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[1]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[1]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[1]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[1]->SetByteCode(nullptr);
  m_rendertargets[1]->Finalize();

  m_rendertargets[2] = mgr->CreateTexture("gAlbedo", vikr_TARGET_2D, "", false);
  m_rendertargets[2]->SetWidth(window->GetWidth());
  m_rendertargets[2]->SetHeight(window->GetHeight());
  m_rendertargets[2]->SetMipmapping(false);
  m_rendertargets[2]->SetMultisampled(false);
  m_rendertargets[2]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[2]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[2]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[2]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[2]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[2]->SetByteCode(nullptr);
  m_rendertargets[2]->Finalize();

  m_rendertargets[3] = mgr->CreateTexture("gSpecular", vikr_TARGET_2D, "", false);
  m_rendertargets[3]->SetWidth(window->GetWidth());
  m_rendertargets[3]->SetHeight(window->GetHeight());
  m_rendertargets[3]->SetMipmapping(false);
  m_rendertargets[3]->SetMultisampled(false);
  m_rendertargets[3]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[3]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[3]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[3]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[3]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[3]->SetByteCode(nullptr);
  m_rendertargets[3]->Finalize();

  m_rendertargets[4] = mgr->CreateTexture("gAmbient", vikr_TARGET_2D, "", false);
  m_rendertargets[4]->SetWidth(window->GetWidth());
  m_rendertargets[4]->SetHeight(window->GetHeight());
  m_rendertargets[4]->SetMipmapping(false);
  m_rendertargets[4]->SetMultisampled(false);
  m_rendertargets[4]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[4]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[4]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[4]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[4]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[4]->SetByteCode(nullptr);
  m_rendertargets[4]->Finalize();

  m_rendertargets[5] = mgr->CreateTexture("gTangent", vikr_TARGET_2D, "", false);
  m_rendertargets[5]->SetWidth(window->GetWidth());
  m_rendertargets[5]->SetHeight(window->GetHeight());
  m_rendertargets[5]->SetMipmapping(false);
  m_rendertargets[5]->SetMultisampled(false);
  m_rendertargets[5]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[5]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[5]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[5]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[5]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[5]->SetByteCode(nullptr);
  m_rendertargets[5]->Finalize();

  m_rendertargets[6] = mgr->CreateTexture("gBitangent", vikr_TARGET_2D, "", false);
  m_rendertargets[6]->SetWidth(window->GetWidth());
  m_rendertargets[6]->SetHeight(window->GetHeight());
  m_rendertargets[6]->SetMipmapping(false);
  m_rendertargets[6]->SetMultisampled(false);
  m_rendertargets[6]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[6]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[6]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[6]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[6]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[6]->SetByteCode(nullptr);
  m_rendertargets[6]->Finalize();

  m_rendertargets[7] = mgr->CreateTexture("gNorm", vikr_TARGET_2D, "", false);
  m_rendertargets[7]->SetWidth(window->GetWidth());
  m_rendertargets[7]->SetHeight(window->GetHeight());
  m_rendertargets[7]->SetMipmapping(false);
  m_rendertargets[7]->SetMultisampled(false);
  m_rendertargets[7]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[7]->SetInternalFormat(vikr_FORMAT_RGB16F);
  m_rendertargets[7]->SetFormat(vikr_FORMAT_RGB);
  m_rendertargets[7]->SetFilterMin(vikr_FILTER_NEAREST);
  m_rendertargets[7]->SetFilterMax(vikr_FILTER_NEAREST);
  m_rendertargets[7]->SetByteCode(nullptr);
  m_rendertargets[7]->Finalize();

  m_rendertargets[8] = mgr->CreateTexture("gDepth", vikr_TARGET_2D, "", false);
  m_rendertargets[8]->SetWidth(window->GetWidth());
  m_rendertargets[8]->SetHeight(window->GetHeight());
  m_rendertargets[8]->SetMipmapping(false);
  m_rendertargets[8]->SetMultisampled(false);
  m_rendertargets[8]->SetDataTypeFormat(vikr_DATATYPE_FLOAT);
  m_rendertargets[8]->SetInternalFormat(vikr_FORMAT_DEPTH);
  m_rendertargets[8]->SetFormat(vikr_FORMAT_DEPTH);
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
  ResourceManager *manager = device->GetResourceManager();
  Shader *vert = manager->CreateShader("vert_gbuffer", vikr_VERTEX_SHADER);
  vert->Compile("../../../libs/shader/GLSL/deferred/gbuffer.vert");
  Shader *frag = manager->CreateShader("frag_gbuffer", vikr_PIXEL_SHADER);
  frag->Compile("../../../libs/shader/GLSL/deferred/gbuffer.frag");
  m_prgm = manager->CreateShaderProgram();
  m_prgm->LoadShader(vert);
  m_prgm->LoadShader(frag);
  m_prgm->Build();

  /**
    Set the RenderPass.
  */
  m_framebuffer->SetRenderPass(m_renderpass);
  m_framebuffer->SetViewport(viewport);
  m_framebuffer->Update();
}


vvoid GBuffer::ExecutePass(CommandbufferList *buffer) {
  if (m_device) {
    m_device->GetContext()->Clear();
    m_device->GetContext()->SetFramebuffer(m_framebuffer);
    m_device->GetContext()->GetPipelineState()->SetShaderProgram(m_prgm);
    m_device->GetContext()->ExecuteCommands(buffer);
  }
}
} // vikr