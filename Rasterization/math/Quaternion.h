#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "Vec3.h"
#include "Vec4.h"

class Vec3;
class Vec4;
class Quaternion
{
public:
	Quaternion(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f, float ww = 1.0f);
    Quaternion(const Vec3& v, float theta);
    Quaternion(const Vec4& v, float theta);
    Quaternion(float thetaX, float thetaY, float thetaZ);


    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator*(float s) const;
    Quaternion operator/(float s) const;

    Quaternion& operator+=(const Quaternion& q);
    Quaternion& operator-=(const Quaternion& q);
    Quaternion& operator*=(float s);
    Quaternion& operator/=(float s);

    void changeVecAndTheta(Vec3 &v, float *theta);
    Quaternion congugate() const;
    Quaternion unitInverse() const;
    Quaternion inverse() const;
    float length() const;
    float length2() const;
    void normalize();
    void print();

    static Quaternion multiply(const Quaternion& p, const Quaternion& q, const Quaternion& r);
	float x, y, z, w;
};



#endif