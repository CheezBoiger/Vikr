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
              c.second->SetDrawOrder(glm::length(camera->GetPos() - location));
            } else {
              c.second->SetDrawOrder(glm::length(location));
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
  CommandBuffer command_buffer; 
  CommandBuffer deferred_buffer;
  RenderContext *context = m_renderDevice->GetContext();
  std::vector<RenderCommand *> &render_commands = m_renderQueue.GetCommandBuffer();
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  for (RenderCommand *command : render_commands) {
    command->Record(&command_buffer);
  }
  std::vector<RenderCommand *> &deferred_commands = m_renderQueue.GetDeferredCommands();
  for(RenderCommand *command : deferred_commands) {
    command->Record(&deferred_buffer);
  }

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  VikrLog::DisplayMessage(VIKR_NOTIFY, "Buffered time: " +
    std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) + "us");
  
  m_gBufferPass->Bind();
  m_renderDevice->GetContext()->Clear();
  m_renderDevice->GetContext()->ClearWithColor(clear_color);
  context->ApplyShaderProgram(gbufferShader->GetProgramId());
  start = std::chrono::steady_clock::now();
  context->ExecuteCommands(&command_buffer);
  end = std::chrono::steady_clock::now();
  VikrLog::DisplayMessage(VIKR_NOTIFY, "gbuffer render time: " +
    std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) + "us");
  m_gBufferPass->Unbind();

  // Deferred Shading pass.

  context->ApplyShaderProgram(lightShader->GetProgramId());
  // This is kind of ridiculous.
  // Might need to think of a newer design.
  {
    ShaderUniformParams params;
    std::map<std::string, MaterialValue> valueset;
    MaterialValue gpos, gnorm, galb, gspec, gamb;
    gpos.m_integer      = 0;
    gpos.type           = vikr_INT;
    gnorm.m_integer     = 1;
    gnorm.type          = vikr_INT; 
    galb.m_integer      = 2;
    galb.type           = vikr_INT;
    gspec.m_integer     = 3; 
    gspec.type          = vikr_INT;
    gamb.m_integer      = 4; 
    gamb.type           = vikr_INT;
    params.uniforms = &valueset;
    params.samplers = nullptr;
    valueset = {
      std::make_pair("gPosition", gpos),
      std::make_pair("gNormal", gnorm),
      std::make_pair("gAlbedo", galb),
      std::make_pair("gSpecular", gspec),
      std::make_pair("gAmbient", gamb)
    };
    context->SetShaderUniforms(&params);
  }

  context->Clear();
  context->ClearWithColor(clear_color);
  for (vuint32 i = 0; i < m_gBufferPass->RenderTextures.size(); ++i) {
    context->SetTexture(m_gBufferPass->RenderTextures[i]->GetTexture(), i);
  }
  context->ExecuteCommands(&deferred_buffer);

  DrawScreenQuad();

  m_renderQueue.Clear();
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
  //m_renderDevice->GetContext()->EnableBlendMode(true);
  m_renderDevice->GetContext()->SetBlendMode(
    BlendFunc::vikr_BLEND_SRC_ALPHA, 
    BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
  m_gBufferPass = std::make_unique<RenderPass>();
  m_gBufferPass->RenderTextures.push_back(m_renderDevice->CreateRenderTexture(1200, 800, false, data_FLOAT));
  m_gBufferPass->RenderTextures.push_back(m_renderDevice->CreateRenderTexture(1200, 800, false, data_FLOAT));
  m_gBufferPass->RenderTextures.push_back(m_renderDevice->CreateRenderTexture(1200, 800, true, data_UNSIGNED_BYTE));
  m_gBufferPass->RenderTextures.push_back(m_renderDevice->CreateRenderTexture(1200, 800, true, data_UNSIGNED_BYTE));
  m_gBufferPass->RenderTextures.push_back(m_renderDevice->CreateRenderTexture(1200, 800, true, data_UNSIGNED_BYTE));
  m_gBufferPass->Depthbuffer = m_renderDevice->CreateRenderbuffer(1200, 800);
  m_gBufferPass->FramebufferObject = m_renderDevice->CreateFramebuffer();
  m_gBufferPass->FramebufferObject->Generate();
  m_gBufferPass->UpdateRenderTargets();
  
  m_renderDevice->GetResourceManager()->StoreShader("gbuffer", "shaders/gbuffer.vert", "shaders/gbuffer.frag");
  gbufferShader = m_renderDevice->GetResourceManager()->GetShader("gbuffer");

  m_renderDevice->GetResourceManager()->StoreShader("lightpass", "shaders/lightpass.vert", "shaders/lightpass.frag");
  lightShader = m_renderDevice->GetResourceManager()->GetShader("lightpass");

  return 1;
}


vvoid Renderer::DrawScreenQuad() {
  CommandBuffer buffer;
  PrimitiveCommand command;
  command.m_mesh = m_quad;
  command.Record(&buffer);
  buffer.Execute(m_renderDevice->GetContext());
}
} // vikr