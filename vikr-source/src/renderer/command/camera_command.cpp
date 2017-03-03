//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/command/camera_command.hpp>
#include <vikr/scene/icamera.hpp>
#include <vikr/scene/camera.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/renderer/renderer.hpp>


namespace vikr {



vvoid CameraCommand::Record(Commandbuffer &buffer) {
  if (camera && (camera == Renderer::GetRenderer()->GetCamera())) {
    m_material.SetMat4("vikr_Projection", camera->GetProjection());
    m_material.SetMat4("vikr_View", camera->GetView());
    m_material.SetVector3fv("vikr_CamPosition", camera->GetPos());
    ShaderUniformParams params;
    params.uniforms = m_material.GetMaterialValues();
    buffer.SetShaderUniforms(params);
  }
}
} // vikr