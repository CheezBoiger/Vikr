/*
  Copyright (c) Mario Garcia. All rights reserved. Like anyone is going to use this shit anyway...
*/
#ifndef __VIKR_MATRIX_H
#define __VIKR_MATRIX_H


namespace vikr {
namespace math {

template<typename _Value = float>
class Matrix2 {
public:
private:
  _Value mat[2][2];
};


template<typename _Value = float >
class Matrix3 {
public:
  Matrix3();
private:
  _Value mat[3][3];
};


template<typename _Value = float>
class Matrix4 {
public:
  Matrix4();


private:


  _Value mat[4][4];
};
} // math
} // vikr
#endif // __VIKR_MATRIX_H