//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/renderer.hpp>
#include <renderer/command/render_command.hpp>
#include <renderer/command/mesh_command.hpp>

#include <scene/camera.hpp>
#include <scene/scene_node.hpp>

#include <mesh/mesh.hpp>

#include <lighting/point_light.hpp>
#include <lighting/spot_light.hpp>
#include <lighting/directional_light.hpp>

#include <util/vikr_log.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <graphics/render_device.hpp>
#include <graphics/render_context.hpp>
#include <graphics/command_buffer.hpp>
#include <graphics/graphics_command.hpp>
#include <resources/resource_manager.hpp>

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
        m_renderQueue.PushBack(command);
        visited.insert(trav);
      }
    }
  }
}


vvoid Renderer::PushBack(Light *command) {
  if (command != nullptr) {
    switch (command->GetLightType()) {
      case vikr_POINTLIGHT:
        m_pointlights.push_back(static_cast<PointLight *>(command)); 
      break;
      case vikr_DIRECTIONLIGHT:
        m_directionallights.push_back(static_cast<DirectionalLight *>(command));
      break;
      case vikr_SPOTLIGHT:
        m_spotlights.push_back(static_cast<SpotLight *>(command));
      break;
      default:
      break;
    }
  }
}


// Cleanup any resources that where handled by the renderer engine.
vint32 Renderer::CleanupResources() {
  return 1;
}


vvoid Renderer::Render() {
  m_renderDevice->GetContext()->Clear();
  m_renderDevice->GetContext()->ClearWithColor(clear_color);
  m_renderQueue.Sort();
  // Record Commands.
  CommandBuffer command_buffer; 
  RenderContext *context = m_renderDevice->GetContext();
  std::vector<RenderCommand *> &render_commands = m_renderQueue.GetCommandBuffer();
  for (RenderCommand *command : render_commands) {
    command->Record(&command_buffer);
  }
  m_renderDevice->GetContext()->ExecuteCommands(&command_buffer);
  m_renderQueue.Clear();
}


vint32 Renderer::Init(RenderDevice *device) {
  m_renderDevice = device;
  m_renderQueue.RegisterBatchComparator([] (RenderCommand *a, RenderCommand *b) -> vint32 {
    if (a->GetCommandType() > b->GetCommandType()) {
      return true;
    } else {
      return false;
    }
  });
  return 1;
}
} // vikr