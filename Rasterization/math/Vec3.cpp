#include "Vec3.h"

const Vec3 Vec3::ZERO = Vec3(0.0f, 0.0f, 0.0f);

Vec3::Vec3()
:x(0),y(0),z(0)
{

}

Vec3::Vec3(float xx, float yy, float zz)
:x(xx),y(yy),z(zz)
{

}

Vec3::Vec3(const Vec3 &p1, const Vec3 &p2) {
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
}

Vec3 Vec3::operator+(const Vec3 &v) const {
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const {
	return Vec3(x - v.x, y - v.y, z - v.z);
}

float Vec3::operator*(const Vec3& v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::operator*(float s) const {
	return Vec3(x * s, y * s, z * s);
}

Vec3 Vec3::operator/(float s) const {
    return Vec3(x / s, y / s, z / s);
}

Vec3 &Vec3::operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3 &Vec3::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vec3 &Vec3::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

bool Vec3::operator==(const Vec3 &v) {
    return (x == v.x && y == v.y && z == v.z);
}

bool Vec3::operator!=(const Vec3 &v) {
    return (x != v.x || y != v.y || z != v.z);
}


Vec3 Vec3::cross(const Vec3 &v) {
	return Vec3(y*v.z-z*v.y, -(x*v.z-z*v.x), x*v.y-y*v.x);
}

float Vec3::length() const{
    return std::sqrt(x * x + y * y + z * z);
}

void Vec3::normalize() {
	float l = length();
	if(l == 0)return;
	x /= l;
	y /= l;
    z /= l;
}

float Vec3::cosTh(const Vec3& v) {
	float d = operator*(v);
	if (d == 0)return 0;
	return d/(length() * v.length());
}


