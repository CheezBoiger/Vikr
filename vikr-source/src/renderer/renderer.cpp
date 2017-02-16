//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/renderer/renderer.hpp>
#include <vikr/renderer/command/render_command.hpp>
#include <vikr/renderer/command/mesh_command.hpp>
#include <vikr/renderer/command/primitive_command.hpp>
#include <vikr/renderer/command/transform_command.hpp>
#include <vikr/renderer/command/camera_command.hpp>

#include <vikr/scene/camera.hpp>
#include <vikr/scene/scene_node.hpp>

#include <vikr/mesh/mesh.hpp>

#include <vikr/shader/material.hpp>

#include <vikr/lighting/point_light.hpp>
#include <vikr/lighting/spot_light.hpp>
#include <vikr/lighting/directional_light.hpp>

#include <vikr/math/shape/quad.hpp>

#include <vikr/util/vikr_log.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vikr/graphics/render_device.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/graphics_command.hpp>
#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/framebuffer.hpp>

#include <vikr/shader/shader_program.hpp>
#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/resources/resource_manager.hpp>

#include <vikr/input/window.hpp>
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
          if(c.second->GetCommandType() == RenderCommandType::COMMAND_TRANSFORM) {
            TransformCommand *tc = static_cast<TransformCommand *>(c.second);
            location = tc->m_transform->Position;
          }
          // In order to sort our command buffer, we need to figure out what objects are 
          // transparent, sort them from shortest to highest distance, and finally
          // draw them after Opaque objects.
          if(camera) {
            c.second->SetDrawOrder(
              static_cast<vint32>(glm::length(camera->GetPos() - location)));
          } else {
            c.second->SetDrawOrder(static_cast<vint32>(glm::length(location)));
          }
          if (c.second->GetCommandType() == RenderCommandType::COMMAND_LIGHT) {
            m_renderQueue.PushBackDeferred(c.second);
          } else {
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
  if(camera) {
    cam.camera = camera;
    PushBack(&cam);
    PushBackDeferred(&cam);
  }

  m_renderQueue.Sort();

  // Record Commands.
  RenderContext *context = m_renderDevice->GetContext();
  std::vector<RenderCommand *> &render_commands = m_renderQueue.GetRenderCommands();
  for(RenderCommand *command : render_commands) {
    std::unique_ptr<Commandbuffer> buf = m_renderDevice->CreateCommandbuffer();
    command->Record(buf.get());
    m_commandBufferList.PushBack(buf);
  }
  std::vector<RenderCommand *> &deferred_commands = m_renderQueue.GetDeferredCommands();
  for(RenderCommand *command : deferred_commands) {
    std::unique_ptr<Commandbuffer> buf = m_renderDevice->CreateCommandbuffer();
    command->Record(buf.get());
    m_deferredBufferList.PushBack(buf);
  }

  // Set the Gbuffer pass.
  m_gbuffer.ExecutePass(&m_commandBufferList);

  // Deferred Shading pass.
  context->SetFramebuffer(nullptr);
  context->Clear();
  // Set back to the default RenderPass.
  context->GetPipelineState()->SetShaderProgram(lightShader);
  for(vuint32 i = 0; i < m_gbuffer.GetNumOfRenderTargets(); ++i) {
    context->SetRenderTarget(m_gbuffer.GetRenderTarget(i), i);
  }
  context->ExecuteCommands(&m_deferredBufferList);

  m_renderQueue.Clear();
  m_commandBufferList.Clear();
  m_deferredBufferList.Clear();

  // Draw the Screen Quad.
  m_screenquad.Execute();
}


vint32 Renderer::Init(RenderDevice *device) {
  Renderer::SetRenderer(this);
  m_renderDevice = device;
  PipelineState *pipeline = 
    device->GetResourceManager()->CreatePipelineState("renderer_pipeline");
  m_renderDevice->GetContext()->ApplyPipelineState(pipeline);
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

  Window *window = Window::GetMainWindow();
  // Create the ScreenQuad.
  m_screenquad.Init(m_renderDevice);

  m_gbuffer.Init(m_renderDevice);
  /*
    Light shader.
  */
  ResourceManager *mgr = m_renderDevice->GetResourceManager();
  Shader *v_lightpass = mgr->CreateShader("lightpass_v", VERTEX_SHADER);
  Shader *f_lightpass = mgr->CreateShader("lightpass_f", FRAGMENT_SHADER);
  v_lightpass->Compile("../../libs/shader/GLSL/lightpass.vert");
  f_lightpass->Compile("../../libs/shader/GLSL/lightpass.frag");
  lightShader = mgr->CreateShaderProgram();
  lightShader->LoadShader(v_lightpass);
  lightShader->LoadShader(f_lightpass);
  lightShader->Build();
  

  // Initialize the light parameters for the light shader.
  m_renderDevice->GetContext()->GetPipelineState()->SetShaderProgram(lightShader);
  m_renderDevice->GetContext()->GetPipelineState()->Update();
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


vvoid Renderer::Present() {
  if (m_renderDevice) {
    m_renderDevice->GetContext()->Present();
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "No Render device iniitialized! No frame to present...");
  }
}
} // vikr