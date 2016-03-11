#ifndef __MATRIX_3D_H_
#define __MATRIX_3D_H_

class Matrix3d
{
public:
    Matrix3d();
    Matrix3d(float m00, float m01, float m02,
         float m10, float m11, float m12,
         float m20, float m21, float m22);
    Matrix3d(const float* m);
    Matrix3d(const Matrix3d& m);
    Matrix3d& operator=(const Matrix3d& m);

    void set(float m00, float m01, float m02,
             float m10, float m11, float m12,
             float m20, float m21, float m22);
    void set(const float* m);
    void set(const Matrix3d& m);

    Matrix3d operator+(const Matrix3d& m);
    Matrix3d operator*(const Matrix3d& m);
    Matrix3d operator*(float s);
    Matrix3d inverse();
    void print(const char* name);
    float mat[3][3];
    
    const static Matrix3d ZERO;
    const static Matrix3d IDENTITY;
};


#endif//__MATRIX_3D_H_


