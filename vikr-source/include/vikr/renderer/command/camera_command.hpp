//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CAMERA_COMMAND_HPP
#define __VIKR_CAMERA_COMMAND_HPP


#include <vikr/renderer/command/render_command.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/shader/shader_config.hpp>
#include <map>


namespace vikr {


class Commandbuffer;
class ICamera;

/**
  CameraCommand sets up camera.
*/
class CameraCommand : public RenderCommand {
public:
  CameraCommand(ICamera *camera = nullptr)
    : RenderCommand(RenderCommandType::COMMAND_CAMERA)
  { }

  vvoid Record(Commandbuffer *buffer) override;

  ICamera *camera;

private:
  std::map<std::string, MaterialValue> camera_params;
}; 
} // vikr 
#endif // __VIKR_CAMERA_COMMAND_HPP