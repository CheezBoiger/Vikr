//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_LIGHT_COMPONENT_HPP
#define __VIKR_LIGHT_COMPONENT_HPP


#include <scene/components/scene_component.hpp>


namespace vikr {


class LightComponent : public SceneComponent {
public:

  LightComponent();

  vvoid Update() override;

  RenderCommand *GetCommand() override;
};
} // vikr
#endif // __VIKR_LIGHT_COMPONENT_HPP