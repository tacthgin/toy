#include "Quaternion.h"
#include "Math.h"
#include <iostream>

Quaternion::Quaternion(float xx, float yy, float zz, float ww)
{
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}

Quaternion::Quaternion(const Vec3 &v, float theta) {
    theta *= 0.5;
    float sinTheta = sin(theta);
    x = sinTheta * v.x;
    y = sinTheta * v.y;
    z = sinTheta * v.z;
    w = cos(theta);
}

Quaternion::Quaternion(const Vec4 &v, float theta) {
    theta *= 0.5;
    float sinTheta = sin(theta);
    x = sinTheta * v.x;
    y = sinTheta * v.y;
    z = sinTheta * v.z;
    w = cos(theta);
}

Quaternion::Quaternion(float thetaX, float thetaY, float thetaZ) {
    thetaX = thetaX * 0.5;
    thetaY = thetaY * 0.5;
    thetaZ = thetaZ * 0.5;

    float cosThetaX = cos(thetaX);
    float cosThetaY = cos(thetaY);
    float cosThetaZ = cos(thetaZ);

    float sinThetaX = sin(thetaX);
    float sinThetaY = sin(thetaY);
    float sinThetaZ = sin(thetaZ);

    w = cosThetaZ * cosThetaY * cosThetaX + sinThetaZ * sinThetaY * sinThetaX;
    x = cosThetaZ * cosThetaY * sinThetaX - sinThetaZ * sinThetaY * cosThetaX;
    y = cosThetaZ * sinThetaY * cosThetaX + sinThetaZ * cosThetaY * sinThetaX;
    z = sinThetaZ * cosThetaY * cosThetaX - cosThetaZ * sinThetaY * sinThetaX;
}

void Quaternion::changeVecAndTheta(Vec3 &v, float *theta) {
    *theta = acos(w);
    float sinTheta = 1 / sin(*theta);

    v.x = x * sinTheta;
    v.y = y * sinTheta;
    v.z = z * sinTheta;

    *theta *= 2;
}

Quaternion Quaternion::operator+(const Quaternion &q) const {
    return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion &q) const {
    return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion Quaternion::operator*(const Quaternion &q) const {
    float prd0 = (z - y) * (q.y - q.z);
    float prd1 = (w + x) * (q.w + q.x);
    float prd2 = (w - x) * (q.y + q.z);
    float prd3 = (y + z) * (q.w - q.x);
    float prd4 = (z - x) * (q.x - q.y);
    float prd5 = (z + x) * (q.x + q.y);
    float prd6 = (w + y) * (q.w - q.z);
    float prd7 = (w - y) * (q.w + q.z);

    float prd8 = prd5 + prd6 + prd7;
    float prd9 = 0.5 * (prd4 + prd8);

    return Quaternion(prd1+prd9-prd8, prd2+prd9-prd7, prd3+prd9-prd6, prd0+prd9-prd5);
}

Quaternion Quaternion::operator*(float s) const {
    return Quaternion(x * s, y * s, z * s, w * s);
}

Quaternion Quaternion::operator/(float s) const {
    return Quaternion(x / s, y / s, z / s, w / s);
}

Quaternion &Quaternion::operator+=(const Quaternion &q) {
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &q) {
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;
    return *this;
}

Quaternion &Quaternion::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
}

Quaternion &Quaternion::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
}

Quaternion Quaternion::congugate() const {
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::unitInverse() const {
    Quaternion ret = *this;
    ret.normalize();
    ret = ret.congugate();

    return ret / ret.length2();
}

Quaternion Quaternion::inverse() const {
    Quaternion ret = this->congugate();
    return ret / ret.length2();
}

float Quaternion::length() const {
    return sqrt(w * w + x * x + y * y + z * z);
}

float Quaternion::length2() const {
    return (w * w + x * x + y * y + z * z);
}

void Quaternion::normalize() {
    *this /= length();
}

void Quaternion::print() {
    using namespace std;
    cout << "Quaternion:" << " x: " << x << " y: " << y << " z: " << z << " w: " << w << endl;
}

Quaternion Quaternion::multiply(const Quaternion &p, const Quaternion &q, const Quaternion &r) {
    return p * q * r;
}
