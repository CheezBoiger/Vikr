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
      case RenderCommandType::RENDER_MESH: {
        MeshCommand *mesh_cmd = static_cast<MeshCommand*>((*it));
        Mesh *mesh = mesh_cmd->GetMesh();
        Material *material = mesh->GetMaterial();
        if (material) {
          Shader *shader = material->GetShader();
          shader->Use();
          glm::mat4 transform;
          transform = glm::translate(camera->GetModelView(), glm::vec3(std::sin(GetTime() * 5), 0.0f, 0.0f));
          mesh->SetModelView(transform);
          shader->SetMat4("modelview", mesh->GetModelView());
          shader->SetMat4("projection", camera->GetProjection());
          //glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "modelview"), 1, GL_FALSE, glm::value_ptr(mesh->GetModelView()));
          //glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "projection"), 1, GL_FALSE,  glm::value_ptr(camera->GetProjection()));
          BindVertexArray(mesh->GetVAO());
          glDrawArrays(GL_TRIANGLES, 0, mesh->GetPositions().size());
          BindVertexArray(0);
        } else {
          VikrLog::DisplayMessage(VIKR_WARNING, "Mesh command rendered with unknown material!!");
        }
      }
    }
  }

  // Clear after.
  m_command_list.Clear();
}
} // vikr