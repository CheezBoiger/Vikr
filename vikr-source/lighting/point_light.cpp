//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <lighting/point_light.hpp>


namespace vikr {


vvoid PointLight::SetConstant(vreal32 constant) {
  m_constant = constant;
}


vvoid PointLight::SetLinear(vreal32 linear) {
  m_linear = linear;
}


vvoid PointLight::SetQuadratic(vreal32 quadratic) {
  m_quadratic = quadratic;
}
} // vikr