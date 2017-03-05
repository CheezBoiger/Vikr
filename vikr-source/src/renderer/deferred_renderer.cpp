//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/renderer/deferred_renderer.hpp>
#include <vikr/renderer/command/render_command.hpp>
#include <vikr/renderer/command/mesh_command.hpp>
#include <vikr/renderer/command/primitive_command.hpp>
#include <vikr/renderer/command/transform_command.hpp>
#include <vikr/renderer/command/camera_command.hpp>

#include <vikr/scene/camera.hpp>
#include <vikr/scene/scene_node.hpp>

#include <vikr/mesh/mesh.hpp>
#include <vikr/platform/vikr_time.hpp>
#include <vikr/shader/material.hpp>

#include <vikr/lighting/point_light.hpp>
#include <vikr/lighting/spot_light.hpp>
#include <vikr/lighting/directional_light.hpp>

#include <vikr/math/geometry/quad.hpp>

#include <vikr/util/vikr_log.hpp>

#include <vikr/graphics/render_device.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/graphics_command.hpp>
#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/framebuffer.hpp>

#include <vikr/shader/shader_program.hpp>
#include <vikr/shader/cubemap.hpp>
#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/scene/first_person_camera.hpp>

#include <vikr/input/window.hpp>
#include <chrono>

#include <set>


namespace vikr {

CameraCommand cam;
GraphicsHardwareInfo gpu_info;
GraphicsPerformanceInfo mem_info;


DeferredRenderer::DeferredRenderer()
  : camera(nullptr)
  , clear_color(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f)) 
{ 
}


vvoid DeferredRenderer::PushBack(RenderCommand *command) {
  if (!command) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Pushed RenderCommand was null! Refusing to push to queue!");
    return;
  }
  m_renderQueue.PushBack(command);
}


vvoid DeferredRenderer::PushBackDeferred(RenderCommand *command) {
  if (command) {
    m_renderQueue.PushBackDeferred(command);
  }
}


/**
  Traverse, from back to front, the provided Scene using 
  Depth-First search method.
*/
vvoid DeferredRenderer::PushBack(SceneNode *obj) {
  if (obj) {
    std::vector<SceneNode *> stack;
    std::set<SceneNode *> visited;
    stack.push_back(obj);
    while (!stack.empty()) {
      SceneNode *trav = stack.back();
      stack.pop_back();
      if (visited.find(trav) == visited.end()) {
        for (auto it : trav->GetChildrenMap()) {
          stack.push_back(it.second);
        }
        GroupCommand &command = trav->GetGroupCommand();
        command.Sort();
        glm::vec3 location = glm::vec3(0.0f);
        for (auto c : command.GetCommands()) {
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
vint32 DeferredRenderer::CleanupResources() {
  return 1;
}


vvoid DeferredRenderer::Render() { 
  m_renderDevice->GetContext()->ClearWithColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  m_renderDevice->GetContext()->Clear();
  if (camera) {
    cam.camera = camera;
    PushBack(&cam);
    PushBackDeferred(&cam);
  }

  m_renderQueue.Sort();

  // Record Commands.
  /*
    TODO(): Need to figure a faster way, Constantly allocating memory on the heap with
            default new! Allocator data structures underway!
  */
  RenderContext *context = m_renderDevice->GetContext();
  std::vector<RenderCommand *> &render_commands = m_renderQueue.GetRenderCommands();
  for (RenderCommand *command : render_commands) {
    Commandbuffer &buf = m_renderDevice->CreateCommandbuffer(m_commandBufferList);
    command->Record(buf);
  }
  std::vector<RenderCommand *> &deferred_commands = m_renderQueue.GetDeferredCommands();
  for (RenderCommand *command : deferred_commands) {
    Commandbuffer &buf = m_renderDevice->CreateCommandbuffer(m_deferredBufferList);
    command->Record(buf);
  }

  // Set the Gbuffer pass.
  m_gbuffer.ExecutePass(m_commandBufferList);
  
  // Deferred Shading pass.
  context->SetFramebuffer(DEFAULT_FRAMEBUFFER);
  
  // Set back to the default RenderPass.
  // Needs to be recorded!!
  context->GetGraphicsPipelineState()->SetShaderProgram(lightShader);
  for(vuint32 i = 0; i < m_gbuffer.GetNumOfRenderTargets(); ++i) {
    context->SetRenderTarget(m_gbuffer.GetRenderTarget(i), i);
  }
  context->ExecuteCommands(m_deferredBufferList);
  

  m_renderQueue.Clear();
  m_commandBufferList->Clear();
  m_deferredBufferList->Clear();

  // Draw the Screen Quad.
  m_screenquad.Execute();

  m_gbuffer.GetFramebuffer()->BlitTo(DEFAULT_FRAMEBUFFER);

  skybox.Execute();

  // Printing stuff. 
  mem_info = m_renderDevice->GetPerformanceInformation();
  printer.SetPrintln("Vikr v0.5", 25.0, 75.0, 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
  printer.SetPrintln("Copyright (c) Mario Garcia, Under the MIT License.", 25.0f,
    25.0f, 0.75f, glm::vec3(1.0f, 1.0f, 1.0f));
  printer.SetPrintln("ms per frame: " + std::to_string(GetFPMS()) + " ms", 
    25.0f, 700.0f, 1.0, glm::vec3(1.0, 1.0, 1.0));
  printer.SetPrintln("Shader Lang: " + m_renderDevice->GetShaderLanguage(), 
    25.0f, 750.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
  printer.SetPrintln("Camera pitch: " + std::to_string(static_cast<FPSCamera *>(camera)->GetPitch()) +
    " Rads", 25.0f, 650.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
  printer.SetPrintln("GPU: " + std::string(gpu_info.renderer), 25.0f, 625, 0.75f, glm::vec3(1.0, 1.0, 1.0));
  printer.SetPrintln("Vendor: " + std::string(gpu_info.vendor), 25.0f, 600, 0.75f, glm::vec3(1.0, 1.0, 1.0));
  printer.SetPrintln("Total GPU memory: " + std::to_string(mem_info.total_mem_kb / 1000) + " MB", 
    25.0f, 575, 0.75f, glm::vec3(1.0, 1.0, 1.0));
  printer.SetPrintln("Available GPU memory: " + std::to_string(mem_info.curr_available_mem_kb / 1000) + " MB", 
    25.0f, 550, 0.75f, glm::vec3(1.0, 1.0, 1.0));
}


vint32 DeferredRenderer::Init(RenderDevice *device, ResourceManager *mgr) {
  if (!Renderer::GetRenderer()) {
    Renderer::SetRenderer(this);
  }
  m_renderDevice = device;
  GraphicsPipelineState *pipeline = 
    device->CreateGraphicsPipelineState("deferred_pipeline");
  m_renderDevice->GetContext()->ApplyGraphicsPipelineState(pipeline);
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
  m_screenquad.Init(m_renderDevice, mgr);
  m_gbuffer.Init(m_renderDevice);
  /*
    Light shader.
  */
  Shader *v_lightpass = device->CreateShader("lightpass_v", vikr_VERTEX_SHADER);
  Shader *f_lightpass = device->CreateShader("lightpass_f", vikr_FRAGMENT_SHADER);
  v_lightpass->Compile("../../../libs/shader/GLSL/deferred/lightpass.vert");
  f_lightpass->Compile("../../../libs/shader/GLSL/deferred/lightpass.frag");
  lightShader = device->CreateShaderProgram();
  lightShader->LoadShader(v_lightpass);
  lightShader->LoadShader(f_lightpass);
  lightShader->Build();
  
  m_commandBufferList = device->CreateCommandbufferList();
  m_deferredBufferList = device->CreateCommandbufferList();

  // Initialize the light parameters for the light shader.
  Commandbuffer &commandbuffer = device->CreateCommandbuffer(m_commandBufferList);

  commandbuffer.BeginRecord();
  commandbuffer.SetShaderProgram(lightShader);
  Material setup;
  setup.SetInt("gPosition", 0);
  setup.SetInt("gNormal", 1);
  setup.SetInt("gAlbedo", 2);
  setup.SetInt("gSpecular", 3);
  setup.SetInt("gAmbient", 4);
  setup.SetInt("gTangent", 5);
  setup.SetInt("gBitangent", 6);
  setup.SetInt("gNorm", 7);
  setup.SetInt("gColor", 8);
  ShaderUniformParams param;
  param.uniforms = setup.GetMaterialValues();
  commandbuffer.SetShaderUniforms(param);
  commandbuffer.EndRecord();

  device->GetContext()->ExecuteCommands(m_commandBufferList);
  m_commandBufferList->Clear();

  // Set the viewport, along with the font type for your printer.
  Viewport port;
  port.win_x = 0;
  port.win_y = 0;
  port.win_width = window->GetWidth();
  port.win_height = window->GetHeight();
  printer.SetViewport(port);
  printer.Init(m_renderDevice, mgr, "c:/windows/fonts/arial.ttf");

  skybox.Init(m_renderDevice, mgr);

  gpu_info = m_renderDevice->GetHardwareInformation();
 
  return 1;
}


vvoid DeferredRenderer::Present() {
  if (m_renderDevice) {
    m_renderDevice->GetContext()->Present();
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "No Render device iniitialized! No frame to present...");
  }
}
} // vikr