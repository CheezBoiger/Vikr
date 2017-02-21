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
  
  


  union {
    struct {
      _Type x;
      _Type y;
      _Type z;
      _Type w;
    };
  };
  
};
} // math
} // vikr
#endif // __VIKR_QUATERNION_HPP