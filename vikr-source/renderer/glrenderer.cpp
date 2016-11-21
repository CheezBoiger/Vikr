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
}


/**
  This will likely fall into it's own resources class.
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


GLenum GLRenderer::GetBlendFunct(BlendFunc blend) {
  GLenum blendfunc = GL_BLEND_DST_ALPHA;
  switch (blend) {
    case BlendFunc::vikr_BLEND_CONSTANT_ALPHA:
      blendfunc = GL_CONSTANT_ALPHA;
    break;
    case BlendFunc::vikr_BLEND_CONSTANT_COLOR:
      blendfunc = GL_CONSTANT_COLOR;
    break;
    case BlendFunc::vikr_BLEND_DST_ALPHA:
      blendfunc = GL_DST_ALPHA;
    break;
    case BlendFunc::vikr_BLEND_DST_COLOR:
      blendfunc = GL_DST_COLOR; 
    break;
    case BlendFunc::vikr_BLEND_GL_ONE_MINUS_CONSTANT_ALPHA:
      blendfunc = GL_ONE_MINUS_CONSTANT_ALPHA;
    break;
    case BlendFunc::vikr_BLEND_ONE:
      blendfunc = GL_ONE;
    break;
    case BlendFunc::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR:
      blendfunc = GL_ONE_MINUS_CONSTANT_COLOR;
    break;
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_ALPHA:
      blendfunc = GL_ONE_MINUS_DST_ALPHA;
    break;
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_COLOR:
      blendfunc = GL_ONE_MINUS_DST_COLOR;
    break;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA:
      blendfunc = GL_ONE_MINUS_SRC1_ALPHA;
    break;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_COLOR:
      blendfunc = GL_ONE_MINUS_SRC_COLOR;
    break;
    case BlendFunc::vikr_BLEND_SRC_ALPHA:
      blendfunc = GL_SRC_ALPHA;
    break;
    case BlendFunc::vikr_BLEND_SRC_COLOR:
      blendfunc = GL_SRC_COLOR;
    break;
    case BlendFunc::vikr_BLEND_ZERO:
      blendfunc = GL_SRC_COLOR;
    break;
  }
  return blendfunc;
}


vint32 GLRenderer::ExecuteMeshCommand(MeshCommand *mesh_cmd) {
  Material *material = mesh_cmd->GetMesh()->GetMaterial();
  glDepthFunc(GLRenderer::GetDepthFunct(material->GetDepthFunc()));
  
  if (material->IsBlending()) {
    glEnable(GL_BLEND);
    
  } else {
    glDisable(GL_BLEND);
  }

  if(material) {
    Shader *shader = material->GetShader();
    shader->Use();
    /**
      TODO(Garcia): Lights need to be individually rendered for each object pass.
     */
    shader->SetMat4("modelview", mesh_cmd->GetTransform());
    shader->SetMat4("projection", camera->GetProjection());
    shader->SetBool("blinn", true);
    shader->SetVector3fv("view_pos", glm::vec3(camera->GetPos().x, camera->GetPos().y, camera->GetPos().z));
   // shader->SetVector3fv("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->SetVector3fv("light_pos", glm::vec3(0.0f, 4.0f, std::sin(GetTime() * 3) * 5));
    shader->SetVector3fv("obj_color", glm::vec3(1.0f, 0.0f, 0.0f));
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