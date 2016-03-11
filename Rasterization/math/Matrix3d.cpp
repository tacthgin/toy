#include "Matrix3d.h"
#include "Math.h"
#include <cstring>
#include <iostream>

#define MATRIX_NUM 9
#define MATRIX_SIZE 3

const Matrix3d Matrix3d::ZERO = Matrix3d(0, 0, 0,
                             0, 0, 0,
                             0, 0, 0);

const Matrix3d Matrix3d::IDENTITY = Matrix3d(1, 0, 0,
                                 0, 1, 0,
                                 0, 0, 1);

Matrix3d::Matrix3d() {
    set(ZERO);
}

Matrix3d::Matrix3d(float m00, float m01, float m02,float m10, float m11, float m12, float m20, float m21, float m22) {
   set(m00, m01, m02, m10, m11, m12, m20, m21, m22);
}

Matrix3d::Matrix3d(const float *m){
    set(m);
}

Matrix3d::Matrix3d(const Matrix3d &m) {
    set(m);
}

Matrix3d &Matrix3d::operator=(const Matrix3d &m) {
    if (this != &m) {
        set(m);
    }

    return *this;
}


void Matrix3d::set(float m00, float m01, float m02,float m10, float m11, float m12, float m20, float m21, float m22) {
    mat[0][0] = m00;
    mat[0][1] = m01;
    mat[0][2] = m02;
    mat[1][0] = m10;
    mat[1][1] = m11;
    mat[1][2] = m12;
    mat[2][0] = m20;
    mat[2][1] = m21;
    mat[2][2] = m22;
}

void Matrix3d::set(const float *m) {
    memcpy(mat, m, sizeof(float) * MATRIX_NUM);
}

void Matrix3d::set(const Matrix3d &m) {
    memcpy(mat, m.mat, sizeof(float) * MATRIX_NUM);
}

Matrix3d Matrix3d::operator+(const Matrix3d &m) {
    Matrix3d ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            ret.mat[i][j] = mat[i][j] + m.mat[i][j];
        }
    }

    return ret;
}

Matrix3d Matrix3d::operator*(const Matrix3d &m) {
    Matrix3d ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                ret.mat[i][j] += mat[i][k] * m.mat[k][j];
            }
        }
    }

    return ret;
}

Matrix3d Matrix3d::operator*(float s) {
    Matrix3d ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            ret.mat[i][j] = mat[i][j] * s;
        }
    }

    return ret;
}

Matrix3d Matrix3d::inverse() {
    float det = mat[0][0] * (mat[1][1] * mat[2][2] -  mat[2][1] * mat[1][2])
                - mat[0][1] * (mat[1][0] * mat[2][2] -  mat[2][0] * mat[1][2])
                + mat[0][2] * (mat[1][0] * mat[2][1] -  mat[2][0] * mat[1][1]);

    if(fabs(det) <= EPSLION_E5)
    {
        return *this;
    }

    Matrix3d inverse;
    inverse.mat[0][0] = mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2];
    inverse.mat[0][1] = -mat[0][1] * mat[2][2] + mat[2][1] * mat[0][2];
    inverse.mat[0][2] = mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2];
    inverse.mat[1][0] = -mat[1][0] * mat[2][2] + mat[2][0] * mat[1][2];
    inverse.mat[1][1] = mat[0][0] * mat[2][2] - mat[2][0] * mat[0][2];
    inverse.mat[1][2] = -mat[0][0] * mat[1][2] + mat[1][0] * mat[0][2];
    inverse.mat[2][0] = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];
    inverse.mat[2][1] = -mat[0][0] * mat[2][1] + mat[2][0] * mat[0][1];
    inverse.mat[2][2] = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];

    return inverse * (1 / det);
}

void Matrix3d::print(const char* name) {
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


