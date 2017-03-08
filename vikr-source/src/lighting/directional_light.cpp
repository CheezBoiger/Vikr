//
// Copyright (c) Mario Gacia, Under the MIT License.
//
#include <vikr/lighting/directional_light.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/shader/shader_program.hpp>
#include <vikr/input/window.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


namespace vikr {


vuint32 DirectionalLight::directionlight_count = 0;


DirectionalLight::DirectionalLight()
  : Light(vikr_DIRECTIONLIGHT
    , glm::vec3(0.0f, 0.0f, 0.0f)
    , directionlight_count
    , glm::vec3(0.2f, 0.2f, 0.2f)
    , glm::vec3(0.01f, 0.01f, 0.01f)
    , glm::vec3(1.0f, 1.0f, 1.0f))
{
  near_plane = 0.0f;
  far_plane = 13000.5f;
  directionlight_count++;
}


vvoid DirectionalLight::Init(RenderDevice *device, ShaderProgram *shadowprogram) {
  m_depthProgram = shadowprogram;
  m_renderDevice = device;
  m_depthTexture = device->CreateTexture("directional_depth_" + std::to_string(m_lightId),
    vikr_TARGET_2D_MULTISAMPLE, "", false);
  m_depthTexture->SetMipmapping(false);
  m_depthTexture->SetFormat(vikr_FORMAT_D32_SFLOAT);
  m_depthTexture->SetWidth(1200);
  m_depthTexture->SetHeight(1024);
  m_depthTexture->SetFilterMin(vikr_FILTER_NEAREST);
  m_depthTexture->SetFilterMax(vikr_FILTER_NEAREST);
  m_depthTexture->SetWrapS(vikr_WRAP_REPEAT);
  m_depthTexture->SetWrapT(vikr_WRAP_REPEAT);
  m_depthTexture->Finalize();

  m_fbo = device->CreateFramebuffer();
  m_fbo->Generate();
  m_fbo->Writebuffer(BUFFER_NONE);
  m_fbo->SetViewport({ 0, 0, 
    Window::GetMainWindow()->GetWidth(), Window::GetMainWindow()->GetHeight() 
  });
  m_renderpass = device->CreateRenderPass();
  m_renderpass->AddRenderTarget(RenderTarget(m_depthTexture), 0);
  
  m_fbo->SetRenderPass(m_renderpass);
  m_fbo->Update();
}


vvoid DirectionalLight::Update() {
  m_lightProjection = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, near_plane, far_plane);
  m_lightView = glm::lookAt(m_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  m_lightSpaceMatrix = m_lightProjection * m_lightView;
}


vvoid DirectionalLight::Execute(CommandbufferList *bufferlist) {
  RenderContext *ctx = m_renderDevice->GetContext();
  ctx->GetGraphicsPipelineState()->SetShaderProgram(m_depthProgram);
  ctx->SetFramebuffer(m_fbo);
  ctx->Clear();
  Material mtl;
  mtl.SetMat4("lightSpaceMatrix", m_lightSpaceMatrix);
  ctx->SetMaterial(&mtl);
  ctx->ExecuteCommands(bufferlist);
}


vvoid DirectionalLight::SetPos(glm::vec3 position)
{
  Light::SetPos(position);
  m_direction = glm::vec3(0.0f, 0.0f, 0.0f) - position;
}
} // vikr