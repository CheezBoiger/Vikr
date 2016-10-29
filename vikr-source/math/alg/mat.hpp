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
  
  Matrix4& operator+(Matrix4& matrix) {
    // Matrix Addition without the need of loop sequence.
    mat[0][0] += matrix[0][0];
    mat[0][1] += matrix[0][1];
    mat[0][2] += matrix[0][2];
    mat[0][3] += matrix[0][3];
    mat[1][0] += matrix[1][0];
    mat[1][1] += matrix[1][1];
    mat[1][2] += matrix[1][2];
    mat[1][3] += matrix[1][3];
    mat[2][0] += matrix[2][0];
    mat[2][1] += matrix[2][1];
    mat[2][2] += matrix[2][2];
    mat[2][3] += matrix[2][3];
    mat[3][0] += matrix[3][0];
    mat[3][1] += matrix[3][1];
    mat[3][2] += matrix[3][2];
    mat[3][3] += matrix[3][3];
    return (*this);
  }


  Matrix4& operator-(Matrix4& matrix) {
    mat[0][0] -= matrix[0][0];
    mat[0][1] -= matrix[0][1];
    mat[0][2] -= matrix[0][2];
    mat[0][3] -= matrix[0][3];
    mat[1][0] -= matrix[1][0];
    mat[1][1] -= matrix[1][1];
    mat[1][2] -= matrix[1][2];
    mat[1][3] -= matrix[1][3];
    mat[2][0] -= matrix[2][0];
    mat[2][1] -= matrix[2][1];
    mat[2][2] -= matrix[2][2];
    mat[2][3] -= matrix[2][3];
    mat[3][0] -= matrix[3][0];
    mat[3][1] -= matrix[3][1];
    mat[3][2] -= matrix[3][2];
    mat[3][3] -= matrix[3][3];
    return (*this);
  }


  Matrix4& operator*(Matrix4& matrix) {
    
  }

  _Value& operator[](unsigned int index) {
    return mat[index];
  }

private:

  // Row major matrix.
  // mat[row][col]
  _Value mat[4][4];
};
} // math
} // vikr
#endif // __VIKR_MATRIX_H