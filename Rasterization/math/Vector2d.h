#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__


class Vector2d
{
public:
    Vector2d();
	Vector2d(float xx, float yy);
	Vector2d(const Vector2d& p1, const Vector2d& p2);

	Vector2d operator+(const Vector2d& v) const;
	Vector2d operator-(const Vector2d& v) const;
	float operator*(const Vector2d& v) const;
	Vector2d operator*(float s) const;
    Vector2d operator/(float s) const;

    Vector2d& operator+=(const Vector2d& v);
    Vector2d& operator-=(const Vector2d& v);
    Vector2d& operator*=(float s);
    Vector2d& operator/=(float s);

    bool operator==(const Vector2d& v);
    bool operator!=(const Vector2d& v);

	Vector2d cross(const Vector2d& v);
	float length() const;
	void normalize();
	float cosTh(const Vector2d& v);
	const static Vector2d ZERO;
	float x, y;
};

#endif //__VECTOR_2D_H__


