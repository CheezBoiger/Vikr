/**
  Copyright (c) Mario Garcia. All rights reserved.
*/
#ifndef __VIKR_VECT_H
#define __VIKR_VECT_H


namespace vikr {


template<typename _Value>
class Vector2 {
public:
private:
  _Value x;
  _Value y;
};


template<typename _Value>
class Vector3 {
public:
private:
  _Value x;
  _Value y;
  _Value z;
};


template<typename _Value>
class Vector4 {
public:
private:

  _Value x;
  _Value y;
  _Value z;
  _Value w;
};
} // vikr
#endif // __VIKR_VECT_H