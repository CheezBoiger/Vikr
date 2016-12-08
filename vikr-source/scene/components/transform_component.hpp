//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TRANSFORM_COMPONENT_HPP
#define __VIKR_TRANSFORM_COMPONENT_HPP


#include <scene/components/scene_component.hpp>
#include <renderer/command/transform_command.hpp>
#include <scene/transform.hpp>


namespace vikr {


/**
  TransformComponent that emits a Transform Command.
*/
class TransformComponent : public SceneComponent {
public:
  TransformComponent(TransformComponent&& t) = default;
  TransformComponent& operator=(TransformComponent&& s) = default;
  TransformComponent();

  vvoid Update() override;

  RenderCommand *GetCommand() override { return &cmd; }

  /**
    World Matrix position.
  */
  vikr::Transform transform;
private:

  /**
    Local transform, relative to the parent.
  */
  vikr::Transform m_localTransform;

  TransformCommand cmd;

  VIKR_DISALLOW_COPY_AND_ASSIGN(TransformComponent);
};
} // vikr
#endif // __VIKR_TRANSFORM_COMPONENT_HPP