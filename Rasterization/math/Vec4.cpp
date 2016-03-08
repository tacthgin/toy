#include "Vec4.h"

const Vec4 Vec4::ZERO = Vec4(0, 0, 0, 0);

Vec4::Vec4()
:x(0),y(0),z(0),w(1)
{

}

Vec4::Vec4(float xx, float yy, float zz, float ww)
:x(xx),y(yy),z(zz),w(ww)
{

}

Vec4::Vec4(const Vec4 &p1, const Vec4 &p2) {
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
    w = 0;
}

Vec4 Vec4::operator+(const Vec4 &v) const{
	return Vec4(x + v.x, y + v.y, z + v.z, w);
}

Vec4 Vec4::operator-(const Vec4& v) const{
	return Vec4(x - v.x, y - v.y, z - v.z, w);
}

float Vec4::operator*(const Vec4& v) const{
	return x * v.x + y * v.y + z * v.z;
}

Vec4 Vec4::operator*(float s) const{
	return Vec4(x * s, y * s, z * s, w);
}

Vec4 Vec4::operator/(float s) const{
    return Vec4(x / s, y / s, z / s, w);
}

Vec4 &Vec4::operator+=(const Vec4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec4 &Vec4::operator*=(const Vec4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vec4 &Vec4::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vec4 &Vec4::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

bool Vec4::operator==(const Vec4 &v) {
    return (x == v.x && y == v.y && z == v.z && w == v.w);
}

bool Vec4::operator!=(const Vec4 &v) {
    return (x != v.x || y != v.y || z != v.z || w != v.w);
}

Vec4 Vec4::cross(const Vec4 &v) {
	return Vec4(y*v.z-z*v.y, -(x*v.z-z*v.x), x*v.y-y*v.x, w);
}

float Vec4::length() const{
	return std::sqrt(x * x + y * y + z * z);
}

void Vec4::normalize() {
	float l = length();
	if(l == 0)return;
	x /= l;
	y /= l;
    z /= l;
}

float Vec4::cosTh(const Vec4& v) {
	float d = operator*(v);
	if (d == 0)return 0;
	return d/(length()*v.length());
}


void Vec4::convertFromHomogenous() {
    if(w == 0)return;
    x /= w;
    y /= w;
    z /= w;
    w /= w;
}


