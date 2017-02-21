//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_QUATERNION_HPP
#define __VIKR_QUATERNION_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/math/alg/vect.hpp>


namespace vikr {
namespace math {



template<typename _Type>
class Quaternion {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Quaternion<_Type>);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Quaternion<_Type>);
  
  Quaternion();
  
  Quaternion Inverse();
  Quaternion Conjugate();


  Quaternion operator+(Quaternion &quat);
  Quaternion operator-(Quaternion &quat);
  Quaternion operator*(Quaternion &quat);
  

  bool operator!=(Quaternion &quat);
  bool operator==(Quaternion &quat);
  
  


  union {
    struct {
      _Type x;
      _Type y;
      _Type z;
      _Type w;
    };
  };
  
};


template<typename _Type>
Quaternion<_Type> AngleAxis(unsigned int angle, Vector3<_Type> &axis);

template<typename _Type>
Quaternion<_Type> Normalize(Quaternion<_Type> &a, Quaternion<_Type> &b);

template<typename _Type>
Quaternion<_Type> Cross(Quaternion<_Type> &a, Quaternion<_Type> &b);

template<typename _Type>
Quaternion<_Type> Dot(Quaternion<_Type> &a, Quaternion<_Type> &b);
} // math
} // vikr
#endif // __VIKR_QUATERNION_HPP