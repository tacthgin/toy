#include "Matrix4d.h"
#include "Math.h"
#include <cstring>
#include <iostream>

#define MATRIX_NUM 16
#define MATRIX_SIZE 4

const Matrix4d Matrix4d::ZERO = Matrix4d(0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0);

const Matrix4d Matrix4d::IDENTITY = Matrix4d(1, 0, 0, 0,
                                 0, 1, 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1);

Matrix4d::Matrix4d() {
    set(ZERO);
}

Matrix4d::Matrix4d(float angleX, float angleY, float angleZ)
{
    float cosTheta = cos(angleX);
    float sinTheta = -sin(angleX);
    
    Matrix4d rx(1, 0, 0, 0,
            0, cosTheta, sinTheta, 0,
            0, -sinTheta, cosTheta, 0,
            0, 0, 0, 1);
    
    cosTheta = cos(angleY);
    sinTheta = -sin(angleY);
    
    Matrix4d ry(cosTheta, 0, -sinTheta, 0,
            0, 1, 0, 0,
            sinTheta, 0, cosTheta, 0,
            0, 0, 0, 1);
    
    cosTheta = cos(angleZ);
    sinTheta = -sin(angleZ);
    
    Matrix4d rz(cosTheta, sinTheta, 0, 0,
            -sinTheta, cosTheta, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    
    this->set(rx * ry * rz);
}

Matrix4d::Matrix4d(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21,
           float m22, float m23, float m30, float m31, float m32, float m33) {
   set(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
}

Matrix4d::Matrix4d(const float *m){
    set(m);
}

Matrix4d::Matrix4d(const Matrix4d &m) {
    set(m);
}

Matrix4d &Matrix4d::operator=(const Matrix4d &m) {
    if (this != &m) {
        set(m);
    }

    return *this;
}


void Matrix4d::set(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
               float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
    mat[0][0] = m00;
    mat[0][1] = m01;
    mat[0][2] = m02;
    mat[0][3] = m03;
    mat[1][0] = m10;
    mat[1][1] = m11;
    mat[1][2] = m12;
    mat[1][3] = m13;
    mat[2][0] = m20;
    mat[2][1] = m21;
    mat[2][2] = m22;
    mat[2][3] = m23;
    mat[3][0] = m30;
    mat[3][1] = m31;
    mat[3][2] = m32;
    mat[3][3] = m33;
}

void Matrix4d::set(const float *m) {
    memcpy(mat, m, sizeof(float) * MATRIX_NUM);
}

void Matrix4d::set(const Matrix4d &m) {
    memcpy(mat, m.mat, sizeof(float) * MATRIX_NUM);
}

Matrix4d Matrix4d::operator+(const Matrix4d &m) {
    Matrix4d ret;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ret.mat[i][j] = mat[i][j] + m.mat[i][j];
        }
    }

    return ret;
}

Matrix4d Matrix4d::operator*(const Matrix4d &m) {
    Matrix4d ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                ret.mat[i][j] += mat[i][k] * m.mat[k][j];
            }
        }
    }

    return ret;
}

Matrix4d Matrix4d::operator*(float s) {
    Matrix4d ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j){
            ret.mat[i][j] = mat[i][j] * s;
        }
    }

    return ret;
}

Matrix4d Matrix4d::inverse() {
    float a0 = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    float a1 = mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0];
    float a2 = mat[0][0] * mat[1][3] - mat[0][3] * mat[1][0];
    float a3 = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1];
    float a4 = mat[0][1] * mat[1][3] - mat[0][3] * mat[1][1];
    float a5 = mat[0][2] * mat[1][3] - mat[0][3] * mat[1][2];
    float b0 = mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0];
    float b1 = mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0];
    float b2 = mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0];
    float b3 = mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1];
    float b4 = mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1];
    float b5 = mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2];

    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

    if (fabs(det) <= EPSLION_E5)
        return *this;

    Matrix4d inverse;
    inverse.mat[0][0]  = mat[1][1] * b5 - mat[1][2] * b4 + mat[1][3] * b3;
    inverse.mat[0][1]  = -mat[0][1] * b5 + mat[0][2] * b4 - mat[0][3] * b3;
    inverse.mat[0][2]  = mat[3][1] * a5 - mat[3][2] * a4 + mat[3][3] * a3;
    inverse.mat[0][3]  = -mat[2][1] * a5 + mat[2][2] * a4 - mat[2][3] * a3;

    inverse.mat[1][0]  = -mat[1][0] * b5 + mat[1][2] * b2 - mat[1][3] * b1;
    inverse.mat[1][1]  = mat[0][0] * b5 - mat[0][2] * b2 + mat[0][3] * b1;
    inverse.mat[1][2]  = -mat[3][0] * a5 + mat[3][2] * a2 - mat[3][3] * a1;
    inverse.mat[1][3]  = mat[2][0] * a5 - mat[2][2] * a2 + mat[2][3] * a1;

    inverse.mat[2][0]  = mat[1][0] * b4 - mat[1][1] * b2 + mat[1][3] * b0;
    inverse.mat[2][1]  = -mat[0][0] * b4 + mat[0][1] * b2 - mat[0][3] * b0;
    inverse.mat[2][2] = mat[3][0] * a4 - mat[3][1] * a2 + mat[3][3] * a0;
    inverse.mat[2][3] = -mat[2][0] * a4 + mat[2][1] * a2 - mat[2][3] * a0;

    inverse.mat[3][0] = -mat[1][0] * b3 + mat[1][1] * b1 - mat[1][2] * b0;
    inverse.mat[3][1] = mat[0][0] * b3 - mat[0][1] * b1 + mat[0][2] * b0;
    inverse.mat[3][2] = -mat[3][0] * a3 + mat[3][1] * a1 - mat[3][2] * a0;
    inverse.mat[3][3] = mat[2][0] * a3 - mat[2][1] * a1 + mat[2][2] * a0;

    return inverse * (1.0f / det);
}

void Matrix4d::print(const char* name) {
    using namespace std;
    cout << name << ":" << "\n";
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

Vec4 operator*(const Vec4& v, const Matrix4d& m)
{
    float ret[4] = {0};
    float array[4] = {v.x, v.y, v.z, v.w};
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ret[i] += array[j] * m.mat[j][i];
        }
    }
    
    return Vec4(ret[0], ret[1], ret[2], ret[3]);
}

