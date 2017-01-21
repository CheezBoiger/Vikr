//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CAMERA_COMMAND_HPP
#define __VIKR_CAMERA_COMMAND_HPP


#include <vikr/renderer/command/render_command.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/renderer/renderer.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/shader/shader_config.hpp>
#include <vikr/scene/icamera.hpp>
#include <vikr/scene/camera.hpp>
#include <map>


namespace vikr {


/**
  CameraCommand sets up camera.
*/
class CameraCommand : public RenderCommand {
public:
  CameraCommand(ICamera *camera = nullptr)
    : RenderCommand(RenderCommandType::COMMAND_CAMERA)
  { }

  vvoid Record(Commandbuffer *buffer) override {
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

  ICamera *camera;

private:
  std::map<std::string, MaterialValue> camera_params;
}; 
} // vikr 
#endif // __VIKR_CAMERA_COMMAND_HPP