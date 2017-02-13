/*
*/
#ifndef __VIKR_MATH_HPP
#define __VIKR_MATH_HPP

#include "alg/mat.hpp"
#include "alg/vect.hpp"


namespace vikr {


template<typename Type>
void Clamp(Type min, Type max, Type &val) {
  if (val > max) {
    val = max;
  } else if (val < min) {
    val = min;
  }
}



using Vec4 = vikr::math::Vector4<float>;
using Vec3 = vikr::math::Vector3<float>;
using Vec2 = vikr::math::Vector2<float>;
using Mat4 = vikr::math::Matrix4<float>;
using Mat3 = vikr::math::Matrix3<float>;
using Mat2 = vikr::math::Matrix2<float>;
} // vikr
#endif // __VIKR_MATH_HPP