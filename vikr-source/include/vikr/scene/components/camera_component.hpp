//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CAMERA_COMPONENT_HPP
#define __VIKR_CAMERA_COMPONENT_HPP


#include <vikr/scene/components/scene_component.hpp>
#include <vikr/scene/icamera.hpp>

#include <vikr/renderer/command/camera_command.hpp>


namespace vikr {


class CameraComponent : public SceneComponent {
public:
  CameraComponent()
    : SceneComponent(vikr_COMPONENT_CAMERA)
  { }

  vvoid Update() override;


  ICamera *camera = nullptr;
private:
  CameraCommand command;
};
} // vikr
#endif // __VIKR_CAMERA_COMPONENT_HPP