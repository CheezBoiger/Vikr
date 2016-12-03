//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/renderer.hpp>
#include <renderer/render_target.hpp>
#include <renderer/render_command.hpp>
#include <renderer/mesh_command.hpp>
#include <renderer/pass.hpp>

#include <scene/camera.hpp>
#include <scene/scene_node.hpp>

#include <mesh/mesh.hpp>

#include <shader/glsl/glsl_compiler.hpp>
#include <shader/spirv/spirv_compiler.hpp>

#include <lighting/point_light.hpp>
#include <lighting/spot_light.hpp>
#include <lighting/directional_light.hpp>

#include <util/vikr_log.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <set>

namespace vikr {


Renderer *Renderer::renderer = nullptr;


Renderer::Renderer(GraphicsPipeline pipeline)
  : renderer_type(pipeline)
  , camera(nullptr)
  , clear_color(glm::vec3(0.1f, 0.1f, 0.1f)) 
{ 
}


vvoid Renderer::PushBack(RenderCommand *command) {
  if (!command) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Pushed RenderCommand was null! Refusing to push to queue!");
    return;
  }
  m_render_queue.PushBack(command, current_renderpass);
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
      SceneNode *trav = stack.front();
      stack.pop_back();
      if (visited.find(trav) == visited.end()) {
        for (auto it : trav->children) {
          stack.push_back(it.second);
        }
        RenderCommand *command = trav->m_render_command;
        m_render_queue.PushBack(command, current_renderpass);
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
      break;
      case vikr_SPOTLIGHT:
      break;
      default:
      break;
    }
  }
}


vvoid Renderer::AddRenderPass(RenderPass *renderpass) {
  m_renderpasses.push_back(renderpass);
}


// Cleanup any resources that where handled by the renderer engine.
vint32 Renderer::CleanupResources() {
  return 1;
}
} // vikr