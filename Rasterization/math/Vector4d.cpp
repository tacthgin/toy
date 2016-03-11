#include "Vector4d.h"

const Vector4d Vector4d::ZERO = Vector4d(0, 0, 0, 0);

Vector4d::Vector4d()
:x(0),y(0),z(0),w(1)
{

}

Vector4d::Vector4d(float xx, float yy, float zz, float ww)
:x(xx),y(yy),z(zz),w(ww)
{

}

Vector4d::Vector4d(const Vector4d &p1, const Vector4d &p2) {
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
    w = 0;
}

Vector4d Vector4d::operator+(const Vector4d &v) const{
	return Vector4d(x + v.x, y + v.y, z + v.z, w);
}

Vector4d Vector4d::operator-(const Vector4d& v) const{
	return Vector4d(x - v.x, y - v.y, z - v.z, w);
}

float Vector4d::operator*(const Vector4d& v) const{
	return x * v.x + y * v.y + z * v.z;
}

Vector4d Vector4d::operator*(float s) const{
	return Vector4d(x * s, y * s, z * s, w);
}

Vector4d Vector4d::operator/(float s) const{
    return Vector4d(x / s, y / s, z / s, w);
}

Vector4d &Vector4d::operator+=(const Vector4d &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector4d &Vector4d::operator-=(const Vector4d &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector4d &Vector4d::operator*=(const Vector4d &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector4d &Vector4d::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector4d &Vector4d::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

bool Vector4d::operator==(const Vector4d &v) {
    return (x == v.x && y == v.y && z == v.z && w == v.w);
}

bool Vector4d::operator!=(const Vector4d &v) {
    return (x != v.x || y != v.y || z != v.z || w != v.w);
}

Vector4d Vector4d::cross(const Vector4d &v) {
	return Vector4d(y*v.z-z*v.y, -(x*v.z-z*v.x), x*v.y-y*v.x, w);
}

float Vector4d::length() const{
	return std::sqrt(x * x + y * y + z * z);
}

void Vector4d::normalize() {
	float l = length();
	if(l == 0)return;
	x /= l;
	y /= l;
    z /= l;
}

float Vector4d::cosTh(const Vector4d& v) {
	float d = operator*(v);
	if (d == 0)return 0;
	return d/(length()*v.length());
}


void Vector4d::convertFromHomogenous() {
    if(w == 0)return;
    x /= w;
    y /= w;
    z /= w;
    w /= w;
}


