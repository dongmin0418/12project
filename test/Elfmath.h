#pragma once

#ifndef ELFMATH_H  // ELFMATH_H�� ���ǵǾ� ���� ������
#define ELFMATH_H  // ELFMATH_H�� �����ϰ� �Ʒ� �ڵ带 ������

#include <stdbool.h>
#include <math.h>
#include "Shape.h"



typedef struct
{
    float m[3][3];  // 3x3 ���
} Matrix3x3;



//�������(Identity Matrix) ����
Matrix3x3 identity_matrix();

//�̵����(Translation Matrix) ����
Matrix3x3 translation_matrix(float dx, float dy);

//ȸ�����(Rotation Matrix) ����
Matrix3x3 rotation_matrix(float theta);

Matrix3x3 rotation_matrix2(float theta);

//ũ���������(Scale Matrix) ���� 
Matrix3x3 scale_matrix(float sx, float sy);

//��İ���
Matrix3x3 multiply_matrices(Matrix3x3 a, Matrix3x3 b);

//���*���� ����
Vector3D multiply_matrix_vector(Matrix3x3 mat, Vector3D v);

Vector3D GetTriangleCenter();

Vector3D GetSquareCenter();
#endif