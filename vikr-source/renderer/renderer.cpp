//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/renderer.hpp>
#include <renderer/render_target.hpp>
#include <renderer/render_command.hpp>
#include <renderer/mesh_command.hpp>

#include <scene/camera.hpp>
#include <scene/scene_obj.hpp>

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
  m_command_list.PushBack(command);
}


vvoid Renderer::PushBack(SceneObject *obj) {
  if (obj) {
    glm::mat4 model;
    glm::mat4 rotation;
    model = glm::translate(model, obj->Transform.Position);
    rotation = glm::toMat4(obj->Transform.Rotation);
    model = model * rotation;
    model = glm::scale(model, obj->Transform.Scale);
    obj->mesh_command.SetTransform(model);
    PushBack(&obj->mesh_command);
    std::vector<SceneObject *> *children = obj->GetChildren();
  }
};


vvoid Renderer::PushBack(Light *command) {
  if (command != nullptr) {
    switch (command->GetLightType()) {
      case vikr_POINTLIGHT:
        m_pointlights.push_back(static_cast<PointLight *>(command));
      break;
    }
  }
};


// Cleanup any resources that where handled by the renderer engine.
vint32 Renderer::CleanupResources() {
  return 1;
}
} // vikr