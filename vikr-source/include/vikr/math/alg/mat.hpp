/*
  Copyright (c) Mario Garcia, under MIT license. Like anyone is going to use this shit anyway...
*/
#ifndef __VIKR_MATRIX_H
#define __VIKR_MATRIX_H

#include <vikr/platform/vikr_api.hpp>
#include <vikr/math/alg/vect.hpp>
#include <vikr/math/alg/quaternion.hpp>

#if defined(__VIKR_SSSE3__)
 #include <tmmintrin.h>
#endif // __VIKR_SSE__

#if defined(__VIKR_SSE__)
 #include <emmintrin.h>
#endif // __VIKR_SSE__


namespace vikr {
namespace math {



template<typename _Type> class Matrix3;
template<typename _Type> class Matrix2;

/// Column Major 4x4 Matrix:
///
/// Design:
///
/// | a00 a01 a02 a03 |
/// | a10 a11 a12 a13 |
/// | a20 a21 a22 a23 |
/// | a30 a31 a32 a33 |
/// 
/// The memory layout is similar to how OpenGL defines matrices
/// in its specifications and blue book. This math library uses the
/// same layout as well.
template<typename _Type = float>
class Matrix4 {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Matrix4<_Type>);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Matrix4<_Type>);
  
  Matrix4(
    Vector4<_Type> &row1, 
    Vector4<_Type> &row2, 
    Vector4<_Type> &row3, 
    Vector4<_Type> &row4) 
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
    _Type a00 = 1, _Type a01 = 0, _Type a02 = 0, _Type a03 = 0,
    _Type a10 = 0, _Type a11 = 1, _Type a12 = 0, _Type a13 = 0,
    _Type a20 = 0, _Type a21 = 0, _Type a22 = 1, _Type a23 = 0,
    _Type a30 = 0, _Type a31 = 0, _Type a32 = 0, _Type a33 = 1) 
  {
    mat[0][0] = a00; mat[0][1] = a01; mat[0][2] = a02; mat[0][3] = a03;
    mat[1][0] = a10; mat[1][1] = a11; mat[1][2] = a12; mat[1][3] = a13;
    mat[2][0] = a20; mat[2][1] = a21; mat[2][2] = a22; mat[2][3] = a23;
    mat[3][0] = a30; mat[3][1] = a31; mat[3][2] = a32; mat[3][3] = a33;
  }

  Matrix4(Matrix3<_Type> &mat1) {
    mat[0][0] = mat1[0][0]; mat[0][1] = mat1[0][1]; mat[0][2] = mat1[0][2]; mat[0][3] = 0;
    mat[1][0] = mat1[1][0]; mat[1][1] = mat1[1][1]; mat[1][2] = mat1[1][2]; mat[1][3] = 0;
    mat[2][0] = mat1[2][0]; mat[2][1] = mat1[2][1]; mat[2][2] = mat1[2][2]; mat[2][3] = 0;
    mat[3][0] = 0;          mat[3][1] = 0;          mat[3][2] = 0;          mat[3][3] = 1;
  }

  static Matrix4 Identity() {
    return Matrix4();
  }
  
  Matrix4 operator+(Matrix4 &mat1) {
    // Matrix Addition without the need of loop sequence.
    return Matrix4(
      mat[0][0] + mat1.mat[0][0], mat[0][1] + mat1.mat[0][1], mat[0][2] + mat1.mat[0][2], mat[0][3] + mat1.mat[0][3],
      mat[1][0] + mat1.mat[1][0], mat[1][1] + mat1.mat[1][1], mat[1][2] + mat1.mat[1][2], mat[1][3] + mat1.mat[1][3],
      mat[2][0] + mat1.mat[2][0], mat[2][1] + mat1.mat[2][1], mat[2][2] + mat1.mat[2][2], mat[2][3] + mat1.mat[2][3],
      mat[3][0] + mat1.mat[3][0], mat[3][1] + mat1.mat[3][1], mat[3][2] + mat1.mat[3][2], mat[3][3] + mat1.mat[3][3]
    );
  }


  Matrix4 operator-(Matrix4 &mat1) {
    return Matrix4(
      mat[0][0] - mat1.mat[0][0], mat[0][1] - mat1.mat[0][1], mat[0][2] - mat1.mat[0][2], mat[0][3] - mat1.mat[0][3],
      mat[1][0] - mat1.mat[1][0], mat[1][1] - mat1.mat[1][1], mat[1][2] - mat1.mat[1][2], mat[1][3] - mat1.mat[1][3],
      mat[2][0] - mat1.mat[2][0], mat[2][1] - mat1.mat[2][1], mat[2][2] - mat1.mat[2][2], mat[2][3] - mat1.mat[2][3],
      mat[3][0] - mat1.mat[3][0], mat[3][1] - mat1.mat[3][1], mat[3][2] - mat1.mat[3][2], mat[3][3] - mat1.mat[3][3]
    );
  }


  Matrix4 operator*(Matrix4 &mat1) {
    return Matrix4(
      mat[0][0] * mat1.mat[0][0] + mat[0][1] * mat1.mat[1][0] + mat[0][2] * mat1.mat[2][0] + mat[0][3] * mat1.mat[3][0],
      mat[0][0] * mat1.mat[0][1] + mat[0][1] * mat1.mat[1][1] + mat[0][2] * mat1.mat[2][1] + mat[0][3] * mat1.mat[3][1],
      mat[0][0] * mat1.mat[0][2] + mat[0][1] * mat1.mat[1][2] + mat[0][2] * mat1.mat[2][2] + mat[0][3] * mat1.mat[3][2],
      mat[0][0] * mat1.mat[0][3] + mat[0][1] * mat1.mat[1][3] + mat[0][2] * mat1.mat[2][3] + mat[0][3] * mat1.mat[3][3],

      mat[1][0] * mat1.mat[0][0] + mat[1][1] * mat1.mat[1][0] + mat[1][2] * mat1.mat[2][0] + mat[1][3] * mat1.mat[3][0],
      mat[1][0] * mat1.mat[0][1] + mat[1][1] * mat1.mat[1][1] + mat[1][2] * mat1.mat[2][1] + mat[1][3] * mat1.mat[3][1],
      mat[1][0] * mat1.mat[0][2] + mat[1][1] * mat1.mat[1][2] + mat[1][2] * mat1.mat[2][2] + mat[1][3] * mat1.mat[3][2],
      mat[1][0] * mat1.mat[0][3] + mat[1][1] * mat1.mat[1][3] + mat[1][2] * mat1.mat[2][3] + mat[1][3] * mat1.mat[3][3],

      mat[2][0] * mat1.mat[0][0] + mat[2][1] * mat1.mat[1][0] + mat[2][2] * mat1.mat[2][0] + mat[2][3] * mat1.mat[3][0],
      mat[2][0] * mat1.mat[0][1] + mat[2][1] * mat1.mat[1][1] + mat[2][2] * mat1.mat[2][1] + mat[2][3] * mat1.mat[3][1],
      mat[2][0] * mat1.mat[0][2] + mat[2][1] * mat1.mat[1][2] + mat[2][2] * mat1.mat[2][2] + mat[2][3] * mat1.mat[3][2],
      mat[2][0] * mat1.mat[0][3] + mat[2][1] * mat1.mat[1][3] + mat[2][2] * mat1.mat[2][3] + mat[2][3] * mat1.mat[3][3],

      mat[3][0] * mat1.mat[0][0] + mat[3][1] * mat1.mat[1][0] + mat[3][2] * mat1.mat[2][0] + mat[3][3] * mat1.mat[3][0],
      mat[3][0] * mat1.mat[0][1] + mat[3][1] * mat1.mat[1][1] + mat[3][2] * mat1.mat[2][1] + mat[3][3] * mat1.mat[3][1],
      mat[3][0] * mat1.mat[0][2] + mat[3][1] * mat1.mat[1][2] + mat[3][2] * mat1.mat[2][2] + mat[3][3] * mat1.mat[3][2],
      mat[3][0] * mat1.mat[0][3] + mat[3][1] * mat1.mat[1][3] + mat[3][2] * mat1.mat[2][3] + mat[3][3] * mat1.mat[3][3]
    );
  }

  _Type *operator[](unsigned int row) {
    return mat[row];
  }

  _Type *GetData() {
    return mat[0];
  }

  _Type *operator*() {
    return mat[0];
  }

  bool operator!=(Matrix4 &mat1) {
    return ( 
      mat[0][0] != mat1.mat[0][0] && mat[0][1] != mat1.mat[0][1] && mat[0][2] != mat1.mat[0][2] && mat[0][3] != mat1.mat[0][3] &&
      mat[1][0] != mat1.mat[1][0] && mat[1][1] != mat1.mat[1][1] && mat[1][2] != mat1.mat[1][2] && mat[1][3] != mat1.mat[1][3] &&
      mat[2][0] != mat1.mat[2][0] && mat[2][1] != mat1.mat[2][1] && mat[2][2] != mat1.mat[2][2] && mat[2][3] != mat1.mat[2][3] &&
      mat[3][0] != mat1.mat[3][0] && mat[3][1] != mat1.mat[3][1] && mat[3][2] != mat1.mat[3][2] && mat[3][3] != mat1.mat[3][3]
    );
  }

  bool operator==(Matrix4 &mat1) {
    return ( 
      mat[0][0] == mat1.mat[0][0] && mat[0][1] == mat1.mat[0][1] && mat[0][2] == mat1.mat[0][2] && mat[0][3] == mat1.mat[0][3] &&
      mat[1][0] == mat1.mat[1][0] && mat[1][1] == mat1.mat[1][1] && mat[1][2] == mat1.mat[1][2] && mat[1][3] == mat1.mat[1][3] &&
      mat[2][0] == mat1.mat[2][0] && mat[2][1] == mat1.mat[2][1] && mat[2][2] == mat1.mat[2][2] && mat[2][3] == mat1.mat[2][3] &&
      mat[3][0] == mat1.mat[3][0] && mat[3][1] == mat1.mat[3][1] && mat[3][2] == mat1.mat[3][2] && mat[3][3] == mat1.mat[3][3]
    );
  }

  /**
    A^T transpose of this matrix.
  */
  Matrix4 Transpose() {
    return Matrix4(
      mat[0][0], mat[1][0], mat[2][0], mat[3][0],
      mat[0][1], mat[1][1], mat[2][1], mat[3][1],
      mat[0][2], mat[1][2], mat[2][2], mat[3][2],
      mat[0][3], mat[1][3], mat[2][3], mat[3][3]
    );
  }

  /**
    Determinant of this Matrix4 ADT
  */
  _Type Determinant() {
    return  mat[0][0] * ( mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - 
                          mat[2][1] * (mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2]) +
                          mat[3][1] * (mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2])
                        ) -
            mat[1][0] * ( mat[0][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) -
                          mat[2][1] * (mat[0][2] * mat[3][3] - mat[0][3] * mat[3][2]) +
                          mat[3][1] * (mat[0][2] * mat[2][3] - mat[0][3] * mat[2][2])
                        ) +
            mat[2][0] * ( mat[0][1] * (mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2]) -
                          mat[1][1] * (mat[0][2] * mat[3][3] - mat[0][3] * mat[3][2]) +
                          mat[3][1] * (mat[0][2] * mat[1][3] - mat[0][3] * mat[1][2])
                        ) -
            mat[3][0] * ( mat[0][1] * (mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2]) -
                          mat[1][1] * (mat[0][2] * mat[2][3] - mat[0][3] * mat[2][2]) +
                          mat[2][1] * (mat[0][2] * mat[1][3] - mat[0][3] * mat[1][2])
                        );
  }

  Matrix4 Inverse() {
    Matrix4 sol;
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
  VIKR_ALIGN(16) _Type mat[4][4];
};


template<typename _Type = float>
class Matrix3 {
public:
  Matrix3(
    Vector3<_Type> &row1,
    Vector3<_Type> &row2,
    Vector3<_Type> &row3)
  {
    mat[0][0] = row1.x; mat[0][1] = row1.y; mat[0][2] = row1.z;
    mat[1][0] = row2.x; mat[1][1] = row2.y; mat[1][2] = row2.z;
    mat[2][0] = row3.x; mat[2][1] = row3.y; mat[2][2] = row3.z;
  }

  Matrix3(
    _Type a00, _Type a01, _Type a02,
    _Type a10, _Type a11, _Type a12,
    _Type a20, _Type a21, _Type a22)
  {
    mat[0][0] = a00; mat[0][1] = a01; mat[0][2] = a02;
    mat[1][0] = a10; mat[1][1] = a11; mat[1][2] = a12;
    mat[2][0] = a20; mat[2][1] = a21; mat[2][2] = a22;
  }


  _Type *operator[](unsigned int i) {
    return mat[i];
  }
private:
 _Type mat[3][3];
};


template<typename _Type = float>
class Matrix2 {
public:
  Matrix2(
    Vector2<_Type> &row1,
    Vector2<_Type> &row2)
  {
  }

  Matrix2(
    _Type a00, _Type a01,
    _Type a10, _Type a11)
  {
  }


private:
  _Type mat[2][2];
};

} // math
} // vikr
#endif // __VIKR_MATRIX_H