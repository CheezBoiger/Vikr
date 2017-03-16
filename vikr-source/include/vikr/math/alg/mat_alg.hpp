// 
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_MATH_ALGEBRA_HPP
#define __VIKR_MATH_ALGEBRA_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/math/alg/vect.hpp>
#include <vikr/math/alg/mat.hpp>
#include <vikr/math/alg/quaternion.hpp>


namespace vikr {
namespace math {


template<typename _Type>
Matrix4<_Type> ToMatrix4(Quaternion<_Type> &quat);

template<typename _Type>
Matrix4<_Type> ToMatrix4(Vector4<_Type> &vec);

template<typename _Type>
Matrix4<_Type> Translate(Matrix4<_Type> &mat, Vector4<_Type> &val);

template<typename _Type>
Matrix4<_Type> Rotate(Matrix4<_Type> &mat, Vector3<_Type> &rot);

template<typename _Type>
Matrix4<_Type> Scale(Matrix4<Type> &mat, Vector3<_Type> &scale);

template<typename _Type>
Matrix4<_Type> EulerAnglesToMatrix(Vector3<_Type> &angle);

template<typename _Type>
Matrix4<_Type> LookAt(Vector3<_Type> &eye, Vector3<_Type> &center, Vector3<_Type> &up);

template<typename _Type>
Matrix4<_Type> Perspective(_Type _fov, _Type _aspect, _Type _near, _Type _far);

template<typename _Type>
Matrix4<_Type> Orthographic(_Type _fov, _Type _aspect, _Type _near, _Type _far);

} // math
} // vikr

#include <vikr/math/alg/impl/mat_alg.inl>

#endif // __VIKR_MATH_ALGEBRA_HPP