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
        MeshCommand *mesh_cmd = static_cast<MeshCommand*>((*it));
        Material *material = mesh_cmd->GetMesh()->GetMaterial();
        if (material) {
          Shader *shader = material->GetShader();
          shader->Use();
          shader->SetMat4("modelview", mesh_cmd->GetTransform());
          shader->SetMat4("projection", camera->GetProjection());
          shader->SetInt("tex", 0);
          ActiveTexture(GL_TEXTURE0);
          BindTexture(GL_TEXTURE_2D, mesh_cmd->GetMesh()->GetTexture()->GetId());
          BindVertexArray(mesh_cmd->GetMesh()->GetVAO());
          DrawArrays(GL_TRIANGLES, 0, mesh_cmd->GetMesh()->GetVertices().size());
          BindVertexArray(0);
          BindTexture(GL_TEXTURE_2D, 0);
        } else {
          VikrLog::DisplayMessage(VIKR_WARNING, "Mesh command rendered with unknown material!!");
        }
      }
    }
  }

  // Clear after.
  m_command_list.Clear();
}


vvoid GLRenderer::ExecuteCommand(RenderCommand *command) {
  

}
} // vikr