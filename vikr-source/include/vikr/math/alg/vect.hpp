/**
  Copyright (c) Mario Garcia. Under the MIT License.
*/
#ifndef __VIKR_VECT_H
#define __VIKR_VECT_H


#include <vikr/platform/vikr_api.hpp>

namespace vikr {
namespace math {


template<typename _Value = float>
class Vector2 {
public:
  Vector2(_Value x = 1.0f,
          _Value y = 1.0f)
  : x(x), y(y) { }


  union {
    struct { _Value x, y; };
    struct { _Value r, g; };
    struct { _Value s, t; };
  };
};


template<typename _Value = float>
class Vector3 {
public:
  Vector3(_Value x = 1.0f, 
          _Value y = 1.0f, 
          _Value z = 1.0f)
  : x(x), y(y), z(z) { }


  union {
    struct { _Value x, y, z; };
    struct { _Value r, g, b; };
    struct { _Value s, t, r; };
  };
};


template<typename _Value = float>
class Vector4 {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Vector4<_Value>);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Vector4<_Value>);
  // Vector4 contruction.
  Vector4(_Value x = 0.0f, 
          _Value y = 0.0f, 
          _Value z = 0.0f , 
          _Value w = 1.0f)
  : x(x), y(y), z(z), w(w) { }


  Vector4 operator+(Vector4 &vec) {
    Vector4 sol;
    sol.x = x + vec.x;
    sol.y = y + vec.y;
    sol.z = z + vec.z;
    sol.w = w + vec.w;
    return sol;
  }

  Vector4 Copy() {
    return Vector4(x, y, z, w);
  }


  union {
    struct { _Value x, y, z, w; };
    struct { _Value r, g, b, a; };
    struct { _Value s, t, r, q; };
  };
};
} // math
} // vikr
#endif // __VIKR_VECT_H