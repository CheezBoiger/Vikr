//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/opengl/glrenderer.hpp>
#include <renderer/renderer.hpp>
#include <renderer/command/render_command.hpp>
#include <renderer/command/mesh_command.hpp>
#include <renderer/command/group_command.hpp>
#include <renderer/command/debug_command.hpp>
#include <renderer/command/primitive_command.hpp>
#include <renderer/command/material_command.hpp>
#include <renderer/command/transform_command.hpp>
#include <renderer/opengl/gl_rendertarget.hpp>
#include <renderer/pass.hpp>

#include <shader/material.hpp>
#include <shader/stb/stb_image.h>
#include <shader/glsl/glsl_shader.hpp>
#include <shader/glsl/gl_texture.hpp>

#include <mesh/opengl/glmesh.hpp>

#include <scene/camera.hpp>
#include <scene/transform.hpp>

#include <util/vikr_log.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <lighting/point_light.hpp>
#include <lighting/light.hpp>

#include <resources/opengl/gl_resource_manager.hpp>


namespace vikr {


GLRenderer::GLRenderer()
  : Renderer(vikr_OPENGL)
{
}


vint32 GLRenderer::Init() {
  GLResourceManager *resource_manager = new GLResourceManager();
  ResourceManager::SetResourceManager(resource_manager);
  /**
    Wait WTF?!?!
  */
  m_render_queue.RegisterBatchComparator([] (RenderCommand *, RenderCommand *) -> vint32 {
    return 0;
  });

  m_render_queue.RegisterDeferredComparator([] (RenderCommand *, RenderCommand *) -> vint32 {
    return 0;
  });
  return true;
}


vvoid GLRenderer::Render() {
  vuint32 original_window_width = camera->GetViewport().win_width;
  vuint32 original_window_height = camera->GetViewport().win_height;
  vreal32 aspect = camera->GetAspect();

  rendering = true;
  ClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);  
  ClearDisplay(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Sort out the m_renderqueue
  Sort();
  // Perform drawing, need to better understand passes for rendering,
  // Pre-batch, batch, and Post-batch drawing.
  if (m_renderpass) {
    Viewport &viewport = 
      m_renderpass->Viewport;

    glViewport(
      viewport.win_x, 
      viewport.win_y, 
      viewport.win_width, 
      viewport.win_height);

    Framebuffer *fbo = m_renderpass->FramebufferObject;

    fbo->Bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glClearColor(fbo->GetClearColor().x,
      fbo->GetClearColor().y,
      fbo->GetClearColor().z, 
      1.0f);
    std::vector<RenderCommand *> *commandBuffer = 
      m_render_queue.GetCommandBuffer();
    for (auto command : *commandBuffer) {
      switch (command->GetCommandType()) {
        case RenderCommandType::COMMAND_MESH:
          ExecuteMeshCommand(static_cast<MeshCommand *>(command));
        break;
        case RenderCommandType::COMMAND_GROUP:
          ExecuteGroupCommand(static_cast<GroupCommand *>(command));
        break;
        case RenderCommandType::COMMAND_PRIMITIVE:
          ExecutePrimitiveCommand(static_cast<PrimitiveCommand *>(command));
        case RenderCommandType::COMMAND_DEBUG:
          ExecuteDebugCommand(static_cast<DebugCommand *>(command));
        break;
        default:
          VikrLog::DisplayMessage(VIKR_ERROR, "Unkown Command to execute! Ignoring.");
        break;
      } 
    }
  }
  
  // TODO(Garcia): Perform Blit and Post processing later on
  // This also requires deferred shading.
  // Restore.
  // Clear after.
  m_render_queue.Clear();
  m_pointlights.clear();
  rendering = false;
}


vint32 GLRenderer::ExecuteMeshCommand(MeshCommand *mesh_cmd) {
  Material *material = mesh_cmd->GetMaterial();

  if(material) {
    current_shader = material->GetShader();
    current_shader->Use();
    current_shader->SetValue("vikr_View", camera->GetView());
    current_shader->SetValue("vikr_Projection", camera->GetProjection());
    current_shader->SetValue("vikr_Model", mesh_cmd->GetTransform());
    current_shader->SetValue("vikr_CamPosition", glm::vec3(camera->GetPos().x,
                                                   camera->GetPos().y, 
                                                   camera->GetPos().z));
    /*
        Algorithm to light a scene!
        1. Render Directional lights first
        2. Render Pointlights second
        3. Render Spotlights last!
    */ 
    for (vuint32 i = 0; i < m_pointlights.size(); ++i) {
      std::string position = "light_pos";
      std::string ambient = "light_ambient";
      std::string diffuse = "light_diffuse";
      std::string specular = "light_specular";
      std::string constant = "constant";
      std::string linear = "linear";
      std::string quadratic = "quadratic";
      current_shader->SetValue("blinn", true);
      current_shader->SetValue(position,  m_pointlights[i]->GetPos());
      current_shader->SetValue(ambient,   m_pointlights[i]->GetAmbient());
      current_shader->SetValue(diffuse,   m_pointlights[i]->GetDiffuse());
      current_shader->SetValue(specular,  m_pointlights[i]->GetSpecular());
      current_shader->SetValue(constant,  m_pointlights[i]->GetConstant());
      current_shader->SetValue(linear,    m_pointlights[i]->GetLinear());
      current_shader->SetValue(quadratic, m_pointlights[i]->GetQuadratic());
    }
    /**
      Require multiple texture targets!
    */
    std::map<std::string, TextureSampler> *samplers = material->GetUniformSamplers();
    std::map<std::string, MaterialValue> *uniforms = material->GetMaterialValues();
    for (std::map<std::string, TextureSampler>::iterator it = samplers->begin();
         it != samplers->end(); ++it) {
      it->second.texture->Bind(it->second.i);
    }
    for (std::map<std::string, MaterialValue>::iterator it = uniforms->begin();
         it != uniforms->end(); ++it) {
      switch (it->second.type) {
        case vikr_INT:    current_shader->SetValue(it->first, it->second.m_integer); break;
        case vikr_FLOAT:  current_shader->SetValue(it->first, it->second.m_float); break;
        case vikr_DOUBLE: current_shader->SetValue(it->first, it->second.m_double); break;
        case vikr_BOOL:   current_shader->SetValue(it->first, it->second.m_bool); break;
        case vikr_VEC2:   current_shader->SetValue(it->first, it->second.m_vec2); break;
        case vikr_VEC3:   current_shader->SetValue(it->first, it->second.m_vec3); break;
        case vikr_VEC4:   current_shader->SetValue(it->first, it->second.m_vec4); break;
        case vikr_MAT2:   current_shader->SetValue(it->first, it->second.m_mat2); break;
        case vikr_MAT3:   current_shader->SetValue(it->first, it->second.m_mat3); break;
        case vikr_MAT4:   current_shader->SetValue(it->first, it->second.m_mat4); break;
        default:          current_shader->SetValue(it->first, it->second.m_integer); break;
      }
    }
    vuint32 vertices = mesh_cmd->GetMesh()->GetVertices().size();
    BindVertexArray(mesh_cmd->GetMesh()->GetVAO());
    switch (mesh_cmd->GetMesh()->GetMeshMode()) {
      case vikr_TRIANGLES: DrawArrays(GL_TRIANGLES, 0, vertices); break;
      case vikr_TRIANGLE_STRIP: DrawArrays(GL_TRIANGLE_STRIP, 0, vertices); break; 
      case vikr_TRIANGLE_FAN: DrawArrays(GL_TRIANGLE_FAN, 0, vertices); break;
      case vikr_TRIANGLE_STRIP_ADJACENCY : DrawArrays(GL_TRIANGLE_STRIP_ADJACENCY, 0, vertices); break;
    }
    //BindVertexArray(0);
  } else {
    VikrLog::DisplayMessage(VIKR_WARNING, "Mesh command rendered with unknown material!!");
  }


  return 1;
}


vvoid GLRenderer::Draw(
  GLenum topology, 
  vuint32 vertices, 
  vuint32 start) 
{
  
}


vint32 GLRenderer::ExecuteDebugCommand(DebugCommand * command) {
  current_shader->SetValue("vikr_Model", glm::mat4());
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(command->GetLineWidth());
  BindVertexArray(command->GetMesh()->GetVAO());
  glDrawArrays(GL_LINES, 0, command->GetMesh()->GetVertices().size());
  glLineWidth(1);
  glDisable(GL_LINE_SMOOTH);
  return 1;
}


vint32 GLRenderer::ExecuteTransformCommand(TransformCommand *command) {
  current_shader->SetValue("vikr_View", camera->GetView());
  current_shader->SetValue("vikr_Projection", camera->GetProjection());
  current_shader->SetValue("vikr_Model", command->m_transform->GetTransform());
  current_shader->SetValue("vikr_CamPosition", glm::vec3(camera->GetPos().x,
                   camera->GetPos().y,
                   camera->GetPos().z));
  return 1;
}


vint32 GLRenderer::ExecutePrimitiveCommand(PrimitiveCommand *command) {
  vuint32 vertices = command->m_mesh->GetVertices().size();
  BindVertexArray(command->m_mesh->GetVAO());
  switch(command->m_mesh->GetMeshMode()) {
  case vikr_TRIANGLES: DrawArrays(GL_TRIANGLES, 0, vertices); break;
  case vikr_TRIANGLE_STRIP: DrawArrays(GL_TRIANGLE_STRIP, 0, vertices); break;
  case vikr_TRIANGLE_FAN: DrawArrays(GL_TRIANGLE_FAN, 0, vertices); break;
  case vikr_TRIANGLE_STRIP_ADJACENCY: DrawArrays(GL_TRIANGLE_STRIP_ADJACENCY, 0, vertices); break;
  }
  return 1;
}


vint32 GLRenderer::ExecuteMaterialCommand(MaterialCommand *command) {
  current_shader = command->m_material->GetShader();
  Material *material = command->m_material;
  current_shader->Use();
  /**
  Require multiple texture targets!
  */
  std::map<std::string, TextureSampler> *samplers = material->GetUniformSamplers();
  std::map<std::string, MaterialValue> *uniforms = material->GetMaterialValues();
  for(std::map<std::string, TextureSampler>::iterator it = samplers->begin();
      it != samplers->end(); ++it) {
    it->second.texture->Bind(it->second.i);
  }
  for(std::map<std::string, MaterialValue>::iterator it = uniforms->begin();
      it != uniforms->end(); ++it) {
    switch(it->second.type) {
    case vikr_INT:    current_shader->SetValue(it->first, it->second.m_integer); break;
    case vikr_FLOAT:  current_shader->SetValue(it->first, it->second.m_float); break;
    case vikr_DOUBLE: current_shader->SetValue(it->first, it->second.m_double); break;
    case vikr_BOOL:   current_shader->SetValue(it->first, it->second.m_bool); break;
    case vikr_VEC2:   current_shader->SetValue(it->first, it->second.m_vec2); break;
    case vikr_VEC3:   current_shader->SetValue(it->first, it->second.m_vec3); break;
    case vikr_VEC4:   current_shader->SetValue(it->first, it->second.m_vec4); break;
    case vikr_MAT2:   current_shader->SetValue(it->first, it->second.m_mat2); break;
    case vikr_MAT3:   current_shader->SetValue(it->first, it->second.m_mat3); break;
    case vikr_MAT4:   current_shader->SetValue(it->first, it->second.m_mat4); break;
    default:          current_shader->SetValue(it->first, it->second.m_integer); break;
    }
  }
  return 1;
}


vint32 GLRenderer::ExecuteGroupCommand(GroupCommand *command) {
  std::vector<std::pair<guid_t, RenderCommand *>> &commands = command->GetCommands();
  for (auto it : commands) {
    switch (it.second->GetCommandType()) {
    case RenderCommandType::COMMAND_MESH: {
      ExecuteMeshCommand(static_cast<MeshCommand *>(it.second));
    } break;
    case RenderCommandType::COMMAND_GROUP: { 
      ExecuteGroupCommand(static_cast<GroupCommand *>(it.second));
    }
    break;
    case RenderCommandType::COMMAND_PRIMITIVE: {
      ExecutePrimitiveCommand(static_cast<PrimitiveCommand *>(it.second));
    }
    break;
    case RenderCommandType::COMMAND_MATERIAL: {
      ExecuteMaterialCommand(static_cast<MaterialCommand *>(it.second));
    }
    break;
    case RenderCommandType::COMMAND_TRANSFORM: {
      ExecuteTransformCommand(static_cast<TransformCommand *>(it.second));
    }
    break;
    case RenderCommandType::COMMAND_DEBUG: {
      ExecuteDebugCommand(static_cast<DebugCommand *>(it.second));
    }
    break;
    default: break;
    }
  }
  return 1;
}
} // vikr