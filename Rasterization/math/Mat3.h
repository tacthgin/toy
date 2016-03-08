#ifndef _MAT_3_H_
#define _MAT_3_H_

class Mat3
{
public:
    Mat3();
    Mat3(float m00, float m01, float m02,
         float m10, float m11, float m12,
         float m20, float m21, float m22);
    Mat3(const float* m);
    Mat3(const Mat3& m);
    Mat3& operator=(const Mat3& m);

    void set(float m00, float m01, float m02,
             float m10, float m11, float m12,
             float m20, float m21, float m22);
    void set(const float* m);
    void set(const Mat3& m);

    Mat3 operator+(const Mat3& m);
    Mat3 operator*(const Mat3& m);
    Mat3 operator*(float s);
    Mat3 inverse();
    void print(const char* name);
    float mat[3][3];
    
    const static Mat3 ZERO;
    const static Mat3 IDENTITY;
};


#endif//_MAT_3_H_


