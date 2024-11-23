#include "ElfMath.h"


//�������(Identity Matrix) ����
Matrix3x3 identity_matrix()
{
    Matrix3x3 mat = {
        {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };
    return mat;
}

//�̵����(Translation Matrix) ����
Matrix3x3 translation_matrix(float dx, float dy)
{
    Matrix3x3 mat = {
        {
            {1.0f, 0.0f, dx},
            {0.0f, 1.0f, dy},
            {0.0f, 0.0f, 1.0f}
        }
    };
    return mat;
}

//ȸ�����(Rotation Matrix) ���� -> �ݽð����
Matrix3x3 rotation_matrix(float theta)
{
    float radians = theta * (3.14159265359f / 180.0f);  // ������ �������� ��ȯ
    Matrix3x3 mat = {
        {
            {cosf(radians), -sinf(radians), 0.0f},
            {sinf(radians), cosf(radians), 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };
    return mat;
}

//ȸ�����(Rotation Matrix) ���� -> �ð����
Matrix3x3 rotation_matrix2(float theta)
{
    float radians = theta * (3.14159265359f / 180.0f);  // ������ �������� ��ȯ
    Matrix3x3 mat = {
        {
            {cosf(radians), sinf(radians), 0.0f},
            {-sinf(radians), cosf(radians), 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };
    return mat;
}


//ũ���������(Scale Matrix) ���� 
Matrix3x3 scale_matrix(float sx, float sy)
{
    Matrix3x3 mat = {
        {
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };
    return mat;
}

//��İ���
Matrix3x3 multiply_matrices(Matrix3x3 a, Matrix3x3 b)
{
    Matrix3x3 result = { {{0}} };

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

Vector3D multiply_matrix_vector(Matrix3x3 mat, Vector3D v)
{
    Vector3D result;
    result.x = mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z;
    result.y = mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z;
    result.z = mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z;
    return result;
}

Vector3D GetTriangleCenter() {
    // �ﰢ�� ������ ��ǥ
    Vector3D a1 = { 15, 10, 1 };
    Vector3D b1 = { 20, 17, 1 };
    Vector3D c1 = { 25, 10, 1 };

    // �߽� ���
    return (Vector3D) {
        (a1.x + b1.x + c1.x) / 3.0f,  // x ��ǥ�� ���
            (a1.y + b1.y + c1.y) / 3.0f,  // y ��ǥ�� ���
            1                             // z ��ǥ (��� �󿡼� ����)
    };
}
Vector3D GetSquareCenter() {
    Vector3D a2 = { 30, 10, 1 };
    Vector3D b2 = { 34, 10, 1 };
    Vector3D c2 = { 34, 14, 1 };
    Vector3D d2 = { 30, 14, 1 };

    return (Vector3D) {
        (a2.x + b2.x + c2.x + d2.x) / 4.0f,
            (a2.y + b2.y + c2.y + d2.y) / 4.0f,
            1
    };
}






