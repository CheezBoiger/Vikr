//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/shadowmap.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/shader/material.hpp>

#include <vikr/input/window.hpp>


namespace vikr {



vvoid DirectionalShadowMap::Init(RenderDevice *device, ResourceManager *mgr) 
{
  if ( !device )  {
    VikrLog::DisplayMessage(VIKR_ERROR, "Null Device used to initialize! Error!!");
    return;
  }

  Shader *vert_depth = device->CreateShader("vert_directionaldepth", vikr_VERTEX_SHADER);
  Shader *frag_depth = device->CreateShader("frag_directionalDepth", vikr_FRAGMENT_SHADER);
  vert_depth->Compile("../../../libs/shader/GLSL/directional_shadowdepth.vert");
  frag_depth->Compile("../../../libs/shader/GLSL/directional_shadowdepth.frag");
  
  m_shadowProgram = device->CreateShaderProgram();
  m_shadowProgram->LoadShader(vert_depth);
  m_shadowProgram->LoadShader(frag_depth);
  m_shadowProgram->Build();

  m_shadowmapFbo = device->CreateFramebuffer();
  m_shadowmapFbo->Generate();
  m_shadowmapFbo->Readbuffer(BUFFER_NONE);
  m_shadowmapFbo->Writebuffer(BUFFER_NONE);

  m_shadowmapRenderPass = device->CreateRenderPass();
  
  m_shadowmapFbo->SetRenderPass(m_shadowmapRenderPass);
  Viewport port;
  port.win_x = 0;
  port.win_y = 0;
  port.win_width = Window::GetMainWindow()->GetWidth();
  port.win_height = Window::GetMainWindow()->GetHeight();
  m_shadowmapFbo->SetViewport(port);
  m_shadowmapFbo->Update();

  m_device = device;
}


vvoid DirectionalShadowMap::Execute(DirectionalLight *light, CommandbufferList *list)
{
  if (!light) {
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG,
      "Light is null! Skipping.");
    return; 
  }
  m_shadowmapRenderPass->RemoveRenderTarget(0);
  m_shadowmapRenderPass->AddRenderTarget(RenderTarget(light->GetDepthMap()), 0);
 
  m_shadowmapFbo->Update();
  RenderContext *ctx = m_device->GetContext();
  ctx->SetFramebuffer(m_shadowmapFbo);
  ctx->Clear();
  ctx->GetGraphicsPipelineState()->SetShaderProgram(m_shadowProgram);
  ctx->GetGraphicsPipelineState()->Update();
  Material mtl;
  mtl.SetMat4("lightSpaceMatrix", light->GetLightSpace());
  ctx->SetMaterial(&mtl);
  
  m_device->GetContext()->ExecuteCommands(list);
}
} // vikr