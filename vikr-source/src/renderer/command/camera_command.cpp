//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/command/camera_command.hpp>
#include <vikr/scene/icamera.hpp>
#include <vikr/scene/camera.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/renderer/renderer.hpp>


namespace vikr {



vvoid CameraCommand::Record(Commandbuffer *buffer) {
  if (camera && (camera == Renderer::GetRenderer()->GetCamera())) {
    MaterialValue projection;
    MaterialValue view;
    MaterialValue position;
    projection.m_mat4 = camera->GetProjection();
    projection.type = vikr_MAT4;
    view.m_mat4 = camera->GetView();
    view.type = vikr_MAT4;
    position.m_vec3 = camera->GetPos();
    position.type = vikr_VEC3;
    camera_params = {
      std::make_pair("vikr_Projection", projection),
      std::make_pair("vikr_View", view),
      std::make_pair("vikr_CamPosition", position)
    };
    //camera_params["cat"] = { vikr_INT, camera->GetPos() };
    ShaderUniformParams params;
    params.uniforms = &camera_params;
    buffer->SetShaderUniforms(params);
  }
}
} // vikr