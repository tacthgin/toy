#include "Vec2.h"

const Vec2 Vec2::ZERO = Vec2(0.0f, 0.0f);

Vec2::Vec2()
:x(0),y(0)
{

}

Vec2::Vec2(float xx, float yy)
:x(xx),y(yy)
{
}

Vec2::Vec2(const Vec2 &p1, const Vec2 &p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
}

Vec2 Vec2::operator+(const Vec2 &v) const {
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const {
    return Vec2(x - v.x, y - v.y);
}

float Vec2::operator*(const Vec2& v) const {
    return x * v.x + y * v.y;
}

Vec2 Vec2::operator*(float s) const {
    return Vec2(x * s, y * s);
}

Vec2 Vec2::operator/(float s) const {
    return Vec2(x / s, y / s);
}

Vec2 &Vec2::operator+=(const Vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vec2 &Vec2::operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
}

Vec2 &Vec2::operator/=(float s) {
    x /= s;
    y /= s;
    return *this;
}

bool Vec2::operator==(const Vec2 &v) {
    return (x == v.x && y == v.y);
}

bool Vec2::operator!=(const Vec2 &v) {
    return (x != v.x || y != v.y);
}

Vec2 Vec2::cross(const Vec2 &v) {
    return ZERO;
}

float Vec2::length() const {
    return std::sqrt(x * x + y * y);
}

void Vec2::normalize() {
    float l = length();
    if(l == 0)return;
    x /= l;
    y /= l;
}

float Vec2::cosTh(const Vec2& v) {
    float d = operator*(v);
    if (d == 0)return 0;
    return d/(length() * v.length());
}

