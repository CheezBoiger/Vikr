//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/renderer.hpp>
#include <renderer/render_target.hpp>
#include <renderer/render_command.hpp>
#include <renderer/mesh_command.hpp>
#include <scene/camera.hpp>
#include <mesh/mesh.hpp>
#include <shader/glsl/glsl_compiler.hpp>
#include <shader/spirv/spirv_compiler.hpp>
#include <lighting/point_light.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


Renderer *Renderer::renderer = nullptr;


Renderer::Renderer(GraphicsPipeline pipeline)
  : renderer_type(pipeline)
  , camera(nullptr)
  , m_current_render_target(nullptr)
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
      mesh->SetRenderTarget(m_current_render_target);
    }
    break;
    default:
    break;
  }
  m_command_list.PushBack(command);
}


vvoid Renderer::PushBack(Light *command) {
  if (command != nullptr) {
    switch (command->GetLightType()) {
      case vikr_POINTLIGHT:
        m_pointlights.PushBack(static_cast<PointLight *>(command));
      break;
    }
  }
};


// Cleanup any resources that where handled by the renderer engine.
vint32 Renderer::CleanupResources() {
  return 1;
}
} // vikr