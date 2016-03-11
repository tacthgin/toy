#ifndef __MATRIX_4D_H__
#define __MATRIX_4D_H__

#include "Vector4d.h"

class Matrix4d
{
public:
    Matrix4d();
    Matrix4d(float angleX, float angleY, float angleZ);
    Matrix4d(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33);
    Matrix4d(const float* m);
    Matrix4d(const Matrix4d& m);
    Matrix4d& operator=(const Matrix4d& m);

    void set(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);
    void set(const float* m);
    void set(const Matrix4d& m);

    Matrix4d operator+(const Matrix4d& m);
    Matrix4d operator*(const Matrix4d& m);
    Matrix4d operator*(float s);

    Matrix4d inverse();
    void print(const char* name);
    
    float mat[4][4];
    
    const static Matrix4d ZERO;
    const static Matrix4d IDENTITY;
};

Vec4 operator*(const Vec4& v, const Matrix4d& m);


#endif//__MATRIX_4D_H__

