//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/lighting/point_light.hpp>


namespace vikr {


/**
  Pointlight count.
*/
vuint32 PointLight::pointlight_count = 0;


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