/*
  Copyright (c) Mario Garcia, under MIT license. Like anyone is going to use this shit anyway...
*/
#ifndef __VIKR_MATRIX_H
#define __VIKR_MATRIX_H

#include <vikr/platform/vikr_api.hpp>
#include <vikr/math/alg/vect.hpp>


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
  Matrix3(
    Vector3<_Value> &row1,
    Vector3<_Value> &row2,
    Vector3<_Value> &row3)
  {
    mat[0][0] = row1.x; mat[0][1] = row1.y; mat[0][2] = row1.z;
    mat[1][0] = row2.x; mat[1][1] = row2.y; mat[1][2] = row2.z;
    mat[2][0] = row3.x; mat[2][1] = row3.y; mat[2][2] = row3.z;
  }

  Matrix3(
    _Value a00, _Value a01, _Value a02,
    _Value a10, _Value a11, _Value a12,
    _Value a20, _Value a21, _Value a22)
  {
    mat[0][0] = a00; mat[0][1] = a01; mat[0][2] = a02;
    mat[1][0] = a10; mat[1][1] = a11; mat[1][2] = a12;
    mat[2][0] = a20; mat[2][1] = a21; mat[2][2] = a22;
  }
private:
  _Value mat[3][3];
};


template<typename _Value = float>
class Matrix4 {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Matrix4<_Value>);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Matrix4<_Value>);
  
  Matrix4(
    Vector4<_Value> &row1, 
    Vector4<_Value> &row2, 
    Vector4<_Value> &row3, 
    Vector4<_Value> &row4) 
  {
    mat[0][0] = row1.x; mat[0][1] = row1.y; mat[0][2] = row1.z; mat[0][3] = row1.w;
    mat[1][0] = row2.x; mat[1][1] = row2.y; mat[1][2] = row2.z; mat[1][3] = row2.w;
    mat[2][0] = row3.x; mat[2][1] = row3.y; mat[2][2] = row3.z; mat[2][3] = row3.w;
    mat[3][0] = row4.x; mat[3][1] = row4.y; mat[3][2] = row4.z; mat[3][3] = row4.w;
  }

  
  /**
    Initialize Column-Major format.
  */
  Matrix4(
    _Value a00 = 1, _Value a01 = 0, _Value a02 = 0, _Value a03 = 0,
    _Value a10 = 0, _Value a11 = 1, _Value a12 = 0, _Value a13 = 0,
    _Value a20 = 0, _Value a21 = 0, _Value a22 = 1, _Value a23 = 0,
    _Value a30 = 0, _Value a31 = 0, _Value a32 = 0, _Value a33 = 1) 
  {
    mat[0][0] = a00; mat[0][1] = a01; mat[0][2] = a02; mat[0][3] = a03;
    mat[1][0] = a10; mat[1][1] = a11; mat[1][2] = a12; mat[1][3] = a13;
    mat[2][0] = a20; mat[2][1] = a21; mat[2][2] = a22; mat[2][3] = a23;
    mat[3][0] = a30; mat[3][1] = a31; mat[3][2] = a32; mat[3][3] = a33;
  }
  
  Matrix4 operator+(Matrix4 &mat1) {
    // Matrix Addition without the need of loop sequence.
    return Matrix4(
      mat[0][0] + mat1.mat[0][0], mat[0][1] + mat1.mat[0][1], mat[0][2] + mat1.mat[0][2], mat[0][3] + mat1.mat[0][3],
      mat[1][0] + mat1.mat[1][0], mat[1][1] + mat1.mat[1][1], mat[1][2] + mat1.mat[1][2], mat[1][3] + mat1.mat[1][3],
      mat[2][0] + mat1.mat[2][0], mat[2][1] + mat1.mat[2][1], mat[2][2] + mat1.mat[2][2], mat[2][3] + mat1.mat[2][3],
      mat[3][0] + mat1.mat[3][0], mat[3][1] + mat1.mat[3][1], mat[3][2] + mat1.mat[3][2], mat[3][3] + mat1.mat[3][3]);
  }


  Matrix4 operator-(Matrix4 &mat1) {
    Matrix4 mat_ans;
    mat_ans[0][0] = mat[0][0] - mat1[0][0];
    mat_ans[0][1] = mat[0][1] - mat1[0][1];
    mat_ans[0][2] = mat[0][2] - mat1[0][2];
    mat_ans[0][3] = mat[0][3] - mat1[0][3];

    mat_ans[1][0] = mat[1][0] - mat1[1][0];
    mat_ans[1][1] = mat[1][1] - mat1[1][1];
    mat_ans[1][2] = mat[1][2] - mat1[1][2];
    mat_ans[1][3] = mat[1][3] - mat1[1][3];

    mat_ans[2][0] = mat[2][0] - mat1[2][0];
    mat_ans[2][1] = mat[2][1] - mat1[2][1];
    mat_ans[2][2] = mat[2][2] - mat1[2][2];
    mat_ans[2][3] = mat[2][3] - mat1[2][3];

    mat_ans[3][0] = mat[3][0] - mat1[3][0];
    mat_ans[3][1] = mat[3][1] - mat1[3][1];
    mat_ans[3][2] = mat[3][1] - mat1[3][2];
    mat_ans[3][3] = mat[3][1] - mat1[3][3];
    return mat_ans;
  }


  Matrix4& operator*(Matrix4& matrix) {
    Matrix4 sol;
    return sol;
  }

  _Value *operator[](unsigned int index) {
    return mat[index];
  }

  _Value *GetData() {
    return mat[0];
  }

  _Value *operator*() {
    return mat[0];
  }

  Matrix4 Transpose() {
    Matrix4 sol;
    return sol;
  }

  Matrix4 Determinant() {
    Matrix4 sol;
    return sol;
  }

  Matrix4 Inverse() {
    Matrix sol;
    return sol;
  }

private:

  // Col-Major matrix.
  // mat[row][col]  (m x n matrix)
  // 
  //  example.
  //       0   1   2   3
  //  0  | 1   5   9  13 |     mat[0][0] = 1    mat[0][1] = 5    mat[0][2] = 9    mat[0][3] = 13 
  //  1  | 2   6  10  14 |     mat[1][0] = 2    mat[1][1] = 6    mat[1][2] = 10   mat[1][3] = 14
  //  2  | 3   7  11  15 |     mat[2][0] = 3    mat[2][1] = 7    mat[2][2] = 11   mat[2][3] = 15
  //  3  | 4   8  12  16 |     mat[3][0] = 4    mat[3][1] = 8    mat[3][2] = 12   mat[3][3] = 16
  _Value mat[4][4];
};
} // math
} // vikr
#endif // __VIKR_MATRIX_H