#include "Mat3.h"
#include "Math.h"
#include <cstring>
#include <iostream>

#define MATRIX_NUM 9
#define MATRIX_SIZE 3

const Mat3 Mat3::ZERO = Mat3(0, 0, 0,
                             0, 0, 0,
                             0, 0, 0);

const Mat3 Mat3::IDENTITY = Mat3(1, 0, 0,
                                 0, 1, 0,
                                 0, 0, 1);

Mat3::Mat3() {
    set(ZERO);
}

Mat3::Mat3(float m00, float m01, float m02,float m10, float m11, float m12, float m20, float m21, float m22) {
   set(m00, m01, m02, m10, m11, m12, m20, m21, m22);
}

Mat3::Mat3(const float *m){
    set(m);
}

Mat3::Mat3(const Mat3 &m) {
    set(m);
}

Mat3 &Mat3::operator=(const Mat3 &m) {
    if (this != &m) {
        set(m);
    }

    return *this;
}


void Mat3::set(float m00, float m01, float m02,float m10, float m11, float m12, float m20, float m21, float m22) {
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

void Mat3::set(const float *m) {
    memcpy(mat, m, sizeof(float) * MATRIX_NUM);
}

void Mat3::set(const Mat3 &m) {
    memcpy(mat, m.mat, sizeof(float) * MATRIX_NUM);
}

Mat3 Mat3::operator+(const Mat3 &m) {
    Mat3 ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            ret.mat[i][j] = mat[i][j] + m.mat[i][j];
        }
    }

    return ret;
}

Mat3 Mat3::operator*(const Mat3 &m) {
    Mat3 ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                ret.mat[i][j] += mat[i][k] * m.mat[k][j];
            }
        }
    }

    return ret;
}

Mat3 Mat3::operator*(float s) {
    Mat3 ret;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            ret.mat[i][j] = mat[i][j] * s;
        }
    }

    return ret;
}

Mat3 Mat3::inverse() {
    float det = mat[0][0] * (mat[1][1] * mat[2][2] -  mat[2][1] * mat[1][2])
                - mat[0][1] * (mat[1][0] * mat[2][2] -  mat[2][0] * mat[1][2])
                + mat[0][2] * (mat[1][0] * mat[2][1] -  mat[2][0] * mat[1][1]);

    if(fabs(det) <= EPSLION_E5)
    {
        return *this;
    }

    Mat3 inverse;
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

void Mat3::print(const char* name) {
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


