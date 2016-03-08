#ifndef _MAT_4_H_
#define _MAT_4_H_

#include "Vec4.h"

class Mat4
{
public:
    Mat4();
    Mat4(float angleX, float angleY, float angleZ);
    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33);
    Mat4(const float* m);
    Mat4(const Mat4& m);
    Mat4& operator=(const Mat4& m);

    void set(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);
    void set(const float* m);
    void set(const Mat4& m);

    Mat4 operator+(const Mat4& m);
    Mat4 operator*(const Mat4& m);
    Mat4 operator*(float s);

    Mat4 inverse();
    void print(const char* name);
    
    float mat[4][4];
    
    const static Mat4 ZERO;
    const static Mat4 IDENTITY;
};

Vec4 operator*(const Vec4& v, const Mat4& m);


#endif//_MAT_4_H_

