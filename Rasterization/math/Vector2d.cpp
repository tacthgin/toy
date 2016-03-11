#include "Vector2d.h"

const Vector2d Vector2d::ZERO = Vector2d(0.0f, 0.0f);

Vector2d::Vector2d()
:x(0),y(0)
{

}

Vector2d::Vector2d(float xx, float yy)
:x(xx),y(yy)
{
}

Vector2d::Vector2d(const Vector2d &p1, const Vector2d &p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
}

Vector2d Vector2d::operator+(const Vector2d &v) const {
	return Vector2d(x + v.x, y + v.y);
}

Vector2d Vector2d::operator-(const Vector2d& v) const {
    return Vector2d(x - v.x, y - v.y);
}

float Vector2d::operator*(const Vector2d& v) const {
    return x * v.x + y * v.y;
}

Vector2d Vector2d::operator*(float s) const {
    return Vector2d(x * s, y * s);
}

Vector2d Vector2d::operator/(float s) const {
    return Vector2d(x / s, y / s);
}

Vector2d &Vector2d::operator+=(const Vector2d &v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2d &Vector2d::operator-=(const Vector2d &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2d &Vector2d::operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
}

Vector2d &Vector2d::operator/=(float s) {
    x /= s;
    y /= s;
    return *this;
}

bool Vector2d::operator==(const Vector2d &v) {
    return (x == v.x && y == v.y);
}

bool Vector2d::operator!=(const Vector2d &v) {
    return (x != v.x || y != v.y);
}

Vector2d Vector2d::cross(const Vector2d &v) {
    return ZERO;
}

float Vector2d::length() const {
    return std::sqrt(x * x + y * y);
}

void Vector2d::normalize() {
    float l = length();
    if(l == 0)return;
    x /= l;
    y /= l;
}

float Vector2d::cosTh(const Vector2d& v) {
    float d = operator*(v);
    if (d == 0)return 0;
    return d/(length() * v.length());
}

