#ifndef _VEC2_H_
#define _VEC2_H_


class Vec2
{
public:
    Vec2();
	Vec2(float xx, float yy);
	Vec2(const Vec2& p1, const Vec2& p2);

	Vec2 operator+(const Vec2& v) const;
	Vec2 operator-(const Vec2& v) const;
	float operator*(const Vec2& v) const;
	Vec2 operator*(float s) const;
    Vec2 operator/(float s) const;

    Vec2& operator+=(const Vec2& v);
    Vec2& operator-=(const Vec2& v);
    Vec2& operator*=(float s);
    Vec2& operator/=(float s);

    bool operator==(const Vec2& v);
    bool operator!=(const Vec2& v);

	Vec2 cross(const Vec2& v);
	float length() const;
	void normalize();
	float cosTh(const Vec2& v);
	const static Vec2 ZERO;
	float x, y;
};

#endif //_VEC2_H_


