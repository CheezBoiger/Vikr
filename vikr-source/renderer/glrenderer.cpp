//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/glrenderer.hpp>
#include <renderer/renderer.hpp>
#include <shader/material.hpp>
#include <shader/shader.hpp>
#include <renderer/render_command.hpp>
#include <renderer/mesh_command.hpp>
#include <mesh/mesh.hpp>
#include <scene/camera.hpp>
#include <util/vikr_log.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader/texture.hpp>
#include <lighting/point_light.hpp>
#include <lighting/light.hpp>

namespace vikr {


GLRenderer::GLRenderer()
  : Renderer(vikr_OPENGL)
{
}


vint32 GLRenderer::Init() {
  return true;
}


vvoid GLRenderer::Render() {
  ClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);  
  ClearDisplay(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Sort out the m_command_list
  Sort();
  
  // Perform drawing, need to better understand passes for rendering,
  // Pre-batch, batch, and Post-batch drawing.
  std::vector<RenderCommand *> render_commands = m_command_list.GetCommandList();
  for (std::vector<RenderCommand *>::iterator it = render_commands.begin();
        it != render_commands.end();
        ++it) {
    switch ((*it)->GetCommandType()) {
      /*
    
        This is not official! Just testing to see Material, Texture, and Mesh work!!
      
      */
      case RenderCommandType::RENDER_MESH: {
        ExecuteMeshCommand(static_cast<MeshCommand *>((*it)));
      }
      break;
      case RenderCommandType::RENDER_GROUP: {
      }
      default:
      break;
    }
  }

  // Clear after.
  m_command_list.Clear();
  m_pointlights.clear();
}


/**
  This will likely fall into it's own resources class. Needs to be handled by 
  Material.
*/
GLenum GLRenderer::GetDepthFunct(DepthFunc funct) {
  GLenum function = GL_LESS;
  switch(funct) {
  case DepthFunc::vikr_DEPTH_ALWAYS:
  function = GL_ALWAYS;
  break;
  case DepthFunc::vikr_DEPTH_EQUAL:
  function = GL_EQUAL;
  break;
  case DepthFunc::vikr_DEPTH_GEQUAL:
  function = GL_GEQUAL;
  break;
  case DepthFunc::vikr_DEPTH_GREATER:
  function = GL_GREATER;
  break;
  case DepthFunc::vikr_DEPTH_LEQUAL:
  function = GL_LEQUAL;
  break;
  case DepthFunc::vikr_DEPTH_LESS:
  function = GL_LESS;
  break;
  case DepthFunc::vikr_DEPTH_NEVER:
  function = GL_NEVER;
  break;
  case DepthFunc::vikr_DEPTH_NOTEQUAL:
  function = GL_NOTEQUAL;
  break;

  }
  return function;
}

/**
  These need to go into Material! Waste of time searching!
*/
GLenum GLRenderer::GetBlendFunct(BlendFunc blend) {
  switch (blend) {
    case BlendFunc::vikr_BLEND_CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;
    case BlendFunc::vikr_BLEND_CONSTANT_COLOR: return GL_CONSTANT_COLOR;
    case BlendFunc::vikr_BLEND_DST_ALPHA: return GL_DST_ALPHA;
    case BlendFunc::vikr_BLEND_DST_COLOR: return GL_DST_COLOR;
    case BlendFunc::vikr_BLEND_GL_ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
    case BlendFunc::vikr_BLEND_ONE: return GL_ONE;
    case BlendFunc::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC1_ALPHA;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
    case BlendFunc::vikr_BLEND_SRC_ALPHA: return GL_SRC_ALPHA;
    case BlendFunc::vikr_BLEND_SRC_COLOR: return GL_SRC_COLOR;
    case BlendFunc::vikr_BLEND_ZERO: return GL_ZERO;
    default: return GL_ZERO;
  }
}


GLenum GLRenderer::GetCullMode(CullFace mode) {
  switch (mode) {
    case CullFace::vikr_CLOCKWISE: return GL_CW;
    case CullFace::vikr_COUNTER_CLOCKWISE: return GL_CCW;
  }
}


GLenum GLRenderer::GetFrontFace(FrontFace face) {
  switch (face) {
    case FrontFace::vikr_FRONT_FACE: return GL_FRONT;
    case FrontFace::vikr_BACK_FACE: return GL_BACK;
    default: return GL_BACK;
  }
}


vint32 GLRenderer::ExecuteMeshCommand(MeshCommand *mesh_cmd) {
  Material *material = mesh_cmd->GetMesh()->GetMaterial();
  glDepthFunc(GLRenderer::GetDepthFunct(material->GetDepthFunc()));
  if (material->IsCulling()) {
    glEnable(GL_CULL_FACE);
    glFrontFace(GLRenderer::GetFrontFace(material->GetFrontFace()));
    glCullFace(GLRenderer::GetCullMode(material->GetCullFace()));
  } else {
    glDisable(GL_CULL_FACE);
  }
  
  if (material->IsBlending()) {
    glEnable(GL_BLEND);
    glBlendFunc(GLRenderer::GetBlendFunct(material->GetBlendSrc()), 
                GLRenderer::GetBlendFunct(material->GetBlendDst()));
  } else {
    glDisable(GL_BLEND);
  }

  if(material) {
    Shader *shader = material->GetShader();
    shader->Use();
    /**
      TODO(Garcia): Lights need to be individually rendered for each object pass. This is 
                    literally hardcoded and needs to be redesigned!
     */

    shader->SetMat4("view", camera->GetView());
    shader->SetMat4("projection", camera->GetProjection());
    shader->SetMat4("model", mesh_cmd->GetTransform());
    shader->SetVector3fv("obj_diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    shader->SetVector3fv("obj_specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->SetVector3fv("view_pos", glm::vec3(camera->GetPos().x, camera->GetPos().y, camera->GetPos().z));
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
      shader->SetBool("blinn", true);
      shader->SetVector3fv(position, m_pointlights[i]->GetPos());
      shader->SetVector3fv(ambient, glm::vec3(0.05f, 0.05f, 0.05f));
      shader->SetVector3fv(diffuse, glm::vec3(0.8f, 0.8f, 0.8f));
      shader->SetVector3fv(specular, glm::vec3(1.0f, 1.0f, 1.0f));
      shader->SetFloat(constant, 1.0f);
      shader->SetFloat(linear, 0.09f);
      shader->SetFloat(quadratic, 0.032f);
    }

    ActiveTexture(GL_TEXTURE0);
    BindTexture(GL_TEXTURE_2D, mesh_cmd->GetMesh()->GetTexture()->GetId());
    BindVertexArray(mesh_cmd->GetMesh()->GetVAO());
    DrawArrays(GL_TRIANGLES, 0, mesh_cmd->GetMesh()->GetVertices().size());
    BindVertexArray(0);
    BindTexture(GL_TEXTURE_2D, 0);
  } else {
    VikrLog::DisplayMessage(VIKR_WARNING, "Mesh command rendered with unknown material!!");
  }


  return 1;
}
} // vikr