#pragma once

#ifndef ELFMATH_H  // ELFMATH_H가 정의되어 있지 않으면
#define ELFMATH_H  // ELFMATH_H를 정의하고 아래 코드를 컴파일

#include <stdbool.h>
#include <math.h>
#include "Shape.h"



typedef struct
{
    float m[3][3];  // 3x3 행렬
} Matrix3x3;



//단위행렬(Identity Matrix) 생성
Matrix3x3 identity_matrix();

//이동행렬(Translation Matrix) 생성
Matrix3x3 translation_matrix(float dx, float dy);

//회전행렬(Rotation Matrix) 생성
Matrix3x3 rotation_matrix(float theta);

Matrix3x3 rotation_matrix2(float theta);

//크기조정행렬(Scale Matrix) 생성 
Matrix3x3 scale_matrix(float sx, float sy);

//행렬곱셈
Matrix3x3 multiply_matrices(Matrix3x3 a, Matrix3x3 b);

//행렬*벡터 곱셈
Vector3D multiply_matrix_vector(Matrix3x3 mat, Vector3D v);

Vector3D GetTriangleCenter();

Vector3D GetSquareCenter();
#endif