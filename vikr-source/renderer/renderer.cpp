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

#include <util/vikr_log.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

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

  switch (command->GetCommandType()) {
    case RenderCommandType::RENDER_MESH: {
      MeshCommand *mesh = static_cast<MeshCommand *>(command);
    }
    break;
    default:
    break;
  }
  m_render_queue.PushBack(command, current_renderpass);
}


vvoid Renderer::PushBack(SceneNode *obj) {
  if (obj) {
    std::vector<SceneNode *> *children = obj->GetChildren();
  }
}


vvoid Renderer::PushBack(Light *command) {
  if (command != nullptr) {
    switch (command->GetLightType()) {
      case vikr_POINTLIGHT:
        m_pointlights.push_back(static_cast<PointLight *>(command));
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