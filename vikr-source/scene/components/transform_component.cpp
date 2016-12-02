//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <scene/components/transform_component.hpp>


namespace vikr {


vvoid TransformComponent::Update() {
  Transform->CalculateTransform();
}
} // vikr