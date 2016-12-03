//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TRANSFORM_COMPONENT_HPP
#define __VIKR_TRANSFORM_COMPONENT_HPP


#include <scene/components/scene_component.hpp>
#include <scene/transform.hpp>


namespace vikr {


class TransformComponent : public SceneComponent {
public:

  vvoid Update() override;

  /**
    World Matrix position.
  */
  vikr::Transform *transform;
private:

  /**
    Local transform, relative to the parent.
  */
  vikr::Transform *m_localTransform;
};
} // vikr
#endif // __VIKR_TRANSFORM_COMPONENT_HPP