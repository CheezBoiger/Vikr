//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CAMERA_COMMAND_HPP
#define __VIKR_CAMERA_COMMAND_HPP


#include <renderer/command/render_command.hpp>
#include <graphics/command_buffer.hpp>
#include <shader/shader_uniform_params.hpp>
#include <shader/shader_config.hpp>
#include <scene/icamera.hpp>
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

  vvoid Record(CommandBuffer *buffer) override {
    if (camera) {
      MaterialValue projection;
      MaterialValue view;
      MaterialValue position;
      projection.m_mat4 = camera->GetProjection();
      projection.type = vikr_MAT4;
      view.m_mat4 = camera->GetView();
      view.type = vikr_MAT4;
      position.m_vec3 = camera->GetPos();
      position.type = vikr_VEC3;
      camera_params["vikr_Projection"] = projection;
      camera_params["vikr_View"] = view;
      camera_params["vikr_CamPosition"] = position;
      ShaderUniformParams params {
        &camera_params,
        nullptr
      };
      buffer->SetShaderUniforms(&params);
    }
  }

  ICamera *camera;

private:
  std::map<std::string, MaterialValue> camera_params;
}; 
} // vikr 
#endif // __VIKR_CAMERA_COMMAND_HPP