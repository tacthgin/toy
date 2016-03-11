#include "Vector3d.h"

const Vector3d Vector3d::ZERO = Vector3d(0.0f, 0.0f, 0.0f);

Vector3d::Vector3d()
:x(0),y(0),z(0)
{

}

Vector3d::Vector3d(float xx, float yy, float zz)
:x(xx),y(yy),z(zz)
{

}

Vector3d::Vector3d(const Vector3d &p1, const Vector3d &p2) {
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
}

Vector3d Vector3d::operator+(const Vector3d &v) const {
	return Vector3d(x + v.x, y + v.y, z + v.z);
}

Vector3d Vector3d::operator-(const Vector3d& v) const {
	return Vector3d(x - v.x, y - v.y, z - v.z);
}

float Vector3d::operator*(const Vector3d& v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vector3d Vector3d::operator*(float s) const {
	return Vector3d(x * s, y * s, z * s);
}

Vector3d Vector3d::operator/(float s) const {
    return Vector3d(x / s, y / s, z / s);
}

Vector3d &Vector3d::operator+=(const Vector3d &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3d &Vector3d::operator-=(const Vector3d &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3d &Vector3d::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector3d &Vector3d::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

bool Vector3d::operator==(const Vector3d &v) {
    return (x == v.x && y == v.y && z == v.z);
}

bool Vector3d::operator!=(const Vector3d &v) {
    return (x != v.x || y != v.y || z != v.z);
}


Vector3d Vector3d::cross(const Vector3d &v) {
	return Vector3d(y*v.z-z*v.y, -(x*v.z-z*v.x), x*v.y-y*v.x);
}

float Vector3d::length() const{
    return std::sqrt(x * x + y * y + z * z);
}

void Vector3d::normalize() {
	float l = length();
	if(l == 0)return;
	x /= l;
	y /= l;
    z /= l;
}

float Vector3d::cosTh(const Vector3d& v) {
	float d = operator*(v);
	if (d == 0)return 0;
	return d/(length() * v.length());
}


