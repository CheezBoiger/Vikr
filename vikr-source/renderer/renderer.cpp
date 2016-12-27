//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/renderer.hpp>
#include <renderer/command/render_command.hpp>
#include <renderer/command/mesh_command.hpp>
#include <renderer/command/primitive_command.hpp>
#include <renderer/command/transform_command.hpp>
#include <renderer/command/camera_command.hpp>

#include <scene/camera.hpp>
#include <scene/scene_node.hpp>

#include <mesh/mesh.hpp>

#include <shader/material.hpp>

#include <lighting/point_light.hpp>
#include <lighting/spot_light.hpp>
#include <lighting/directional_light.hpp>

#include <math/shape/quad.hpp>

#include <util/vikr_log.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <graphics/render_device.hpp>
#include <graphics/render_context.hpp>
#include <graphics/command_buffer.hpp>
#include <graphics/graphics_command.hpp>
#include <graphics/blendmode.hpp>
#include <graphics/framebuffer.hpp>
#include <resources/resource_manager.hpp>

#include <input/window.hpp>
#include <chrono>

#include <set>


namespace vikr {


Renderer *Renderer::renderer = nullptr;


Renderer::Renderer()
  : camera(nullptr)
  , clear_color(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f)) 
{ 
}


vvoid Renderer::PushBack(RenderCommand *command) {
  if (!command) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Pushed RenderCommand was null! Refusing to push to queue!");
    return;
  }
  m_renderQueue.PushBack(command);
}


vvoid Renderer::PushBackDeferred(RenderCommand *command) {
  if (command) {
    m_renderQueue.PushBackDeferred(command);
  }
}


/**
  Traverse, from back to front, the provided Scene using 
  Depth-First search method.
*/
vvoid Renderer::PushBack(SceneNode *obj) {
  if (obj) {
    std::vector<SceneNode *> stack;
    std::set<SceneNode *> visited;
    stack.push_back(obj);
    while (!stack.empty()) {
      SceneNode *trav = stack.back();
      stack.pop_back();
      if (visited.find(trav) == visited.end()) {
        for (auto it : trav->children) {
          stack.push_back(it.second);
        }
        GroupCommand *command = &trav->m_commandList;
        command->Sort();
        glm::vec3 location = glm::vec3(0.0f);
        for (auto c : command->GetCommands()) {
          if (c.second->GetCommandType() == RenderCommandType::COMMAND_LIGHT) {
            m_renderQueue.PushBackDeferred(c.second);
          } else {
            if (c.second->GetCommandType() == RenderCommandType::COMMAND_TRANSFORM) {
              TransformCommand *tc = static_cast<TransformCommand *>(c.second);
              location = tc->m_transform->Position;
            }
            // In order to sort our command buffer, we need to figure out what objects are 
            // transparent, sort them from shortest to highest distance, and finally
            // draw them after Opaque objects.
            if (camera) {
              c.second->SetDrawOrder(
                static_cast<vint32>(glm::length(camera->GetPos() - location)));
            } else {
              c.second->SetDrawOrder(static_cast<vint32>(glm::length(location)));
            }
            m_renderQueue.PushBack(c.second);
          }
        }
        visited.insert(trav);
      }
    }
  }
}


// Cleanup any resources that where handled by the renderer engine.
vint32 Renderer::CleanupResources() {
  return 1;
}


vvoid Renderer::Render() {
  CameraCommand cam;
  if (camera) {
    cam.camera = camera;
    PushBack(&cam);
    PushBackDeferred(&cam);
  }

  m_renderQueue.Sort();

  // Record Commands.
  RenderContext *context = m_renderDevice->GetContext();
  std::vector<RenderCommand *> &render_commands = m_renderQueue.GetCommandBuffer();
  for (RenderCommand *command : render_commands) {
    std::unique_ptr<Commandbuffer> buf = m_renderDevice->CreateCommandbuffer();
    command->Record(buf.get());
    m_commandBuffer.PushBack(buf);
  }
  std::vector<RenderCommand *> &deferred_commands = m_renderQueue.GetDeferredCommands();
  for(RenderCommand *command : deferred_commands) {
    std::unique_ptr<Commandbuffer> buf = m_renderDevice->CreateCommandbuffer();
    command->Record(buf.get());
    m_deferredBuffer.PushBack(buf);
  }
  
  // Set the Gbuffer pass.
  context->SetRenderPass(m_gBufferPass.get());
  context->ApplyShaderProgram(gbufferShader->GetProgramId());
  context->ExecuteCommands(&m_commandBuffer);

  // Deferred Shading pass.

  
  // Set back to the default RenderPass.
  context->SetRenderPass(nullptr);
  context->ApplyShaderProgram(lightShader->GetProgramId());
  for (vuint32 i = 0; i < m_gBufferPass->RenderTargets.size(); ++i) {
    context->SetRenderTarget(m_gBufferPass->RenderTargets[i].get(), i);   
  }
  context->ExecuteCommands(&m_deferredBuffer);

  m_renderQueue.Clear();
  m_commandBuffer.Clear();
  m_deferredBuffer.Clear();

  DrawScreenQuad();
}


vint32 Renderer::Init(RenderDevice *device) {
  Renderer::SetRenderer(this);
  m_renderDevice = device;
  m_renderQueue.RegisterBatchComparator([&] (RenderCommand *a, RenderCommand *b) -> vint32 {
    vint32 greater = false;
    //if (a->GetDrawOrder() > b->GetDrawOrder()) {
    //  greater = true;
    //}
    return greater;
  });
  m_renderQueue.RegisterDeferredComparator([] (RenderCommand *command1, RenderCommand *command2) -> vint32 {
    return false;
  });
  m_renderDevice->GetContext()->EnableDepthMode(true);
  m_renderDevice->GetContext()->EnableCullMode(true);


  // Create the ScreenQuad.
  Quad quad;
  m_quad = m_renderDevice->GetResourceManager()->CreateMesh(quad.GetPositions(), 
    quad.GetNormals(), quad.GetUVs());
  m_quad->Create(m_renderDevice);

  // gbuffer 
  /**
    TODO(): Be sure to set these numbers (1200, 800) into the size of the screen, since
            right now there is no telling what the screen size is at the moment. This is
            practically hardcoded.
  */
  m_gBufferPass = m_renderDevice->CreateRenderPass();
  m_gBufferPass->Viewport.win_x = 0;
  m_gBufferPass->Viewport.win_y = 0;
  m_gBufferPass->Viewport.win_width = Window::GetWindowWidth();
  m_gBufferPass->Viewport.win_height = Window::GetWindowHeight();
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gPosition", 
      Window::GetWindowWidth(), Window::GetWindowHeight(), false, data_FLOAT));
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gNormal", 
      Window::GetWindowWidth(), Window::GetWindowHeight(), true, data_UNSIGNED_BYTE));
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gAlbedo", 
      Window::GetWindowWidth(), Window::GetWindowHeight(), true, data_UNSIGNED_BYTE));
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gSpecular", 
      Window::GetWindowWidth(), Window::GetWindowHeight(), true, data_UNSIGNED_BYTE));
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gAmbient" , 
      Window::GetWindowWidth(), Window::GetWindowHeight(), true, data_UNSIGNED_BYTE));
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gTangent",
      Window::GetWindowWidth(), Window::GetWindowHeight(), false, data_FLOAT));
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gBitangent",
      Window::GetWindowWidth(), Window::GetWindowHeight(), false, data_FLOAT));
  m_gBufferPass->RenderTargets
    .push_back(m_renderDevice->CreateRenderTexture("gNorm",
               Window::GetWindowWidth(), Window::GetWindowHeight(), false, data_FLOAT));
  m_gBufferPass->Depthbuffer = m_renderDevice->CreateRenderbuffer(Window::GetWindowWidth(), 
    Window::GetWindowHeight());

  m_gBufferPass->FramebufferObject = m_renderDevice->CreateFramebuffer();
  m_gBufferPass->FramebufferObject->Generate();
  m_gBufferPass->UpdateRenderTargets();

  /*
    Gbuffer shader.
  */
  m_renderDevice->GetResourceManager()->StoreShader("gbuffer", "shaders/gbuffer.vert", "shaders/gbuffer.frag");
  gbufferShader = m_renderDevice->GetResourceManager()->GetShader("gbuffer");

  m_renderDevice->GetContext()->ApplyShaderProgram(gbufferShader->GetProgramId());
  /*
    Light shader.
  */
  m_renderDevice->GetResourceManager()->StoreShader("lightpass", "shaders/lightpass.vert", "shaders/lightpass.frag");
  lightShader = m_renderDevice->GetResourceManager()->GetShader("lightpass");
  

  // Initialize the light parameters for the light shader.
  m_renderDevice->GetContext()->ApplyShaderProgram(lightShader->GetProgramId());
  Material setup;
  setup.SetInt("gPosition", 0);
  setup.SetInt("gNormal", 1);
  setup.SetInt("gAlbedo", 2);
  setup.SetInt("gSpecular", 3);
  setup.SetInt("gAmbient", 4);
  setup.SetInt("gTangent", 5);
  setup.SetInt("gBitangent", 6);
  setup.SetInt("gNorm", 7);
  ShaderUniformParams param;
  param.uniforms = setup.GetMaterialValues();
  m_renderDevice->GetContext()->SetShaderUniforms(&param);

  return 1;
}


vvoid Renderer::DrawScreenQuad() {
  std::unique_ptr<Commandbuffer > buffer = m_renderDevice->CreateCommandbuffer();
  PrimitiveCommand command;
  command.m_mesh = m_quad;
  command.Record(buffer.get());
  m_commandBuffer.PushBack(buffer);
  m_renderDevice->GetContext()->ExecuteCommands(&m_commandBuffer);
  m_commandBuffer.Clear();
}
} // vikr