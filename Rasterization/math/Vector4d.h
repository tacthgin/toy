#ifndef __VECTOR_4D_H__
#define __VECTOR_4D_H__

class Vector4d
{
public:
    Vector4d();
	Vector4d(float xx, float yy, float zz, float ww);
	Vector4d(const Vector4d& p1, const Vector4d& p2);

	Vector4d operator+(const Vector4d& v) const;
	Vector4d operator-(const Vector4d& v) const;
	float operator*(const Vector4d& v) const;
	Vector4d operator*(float s) const;
    Vector4d operator/(float s) const;

    Vector4d& operator+=(const Vector4d& v);
    Vector4d& operator-=(const Vector4d& v);
    Vector4d& operator*=(const Vector4d& v);
    Vector4d& operator*=(float s);
    Vector4d& operator/=(float s);

    bool operator==(const Vector4d& v);
    bool operator!=(const Vector4d& v);

	Vector4d cross(const Vector4d& v);
	float length() const;
	void normalize();
	float cosTh(const Vector4d& v);
    void convertFromHomogenous();

	const static Vector4d ZERO;
	float x, y, z, w;
};

#endif //__VECTOR_4D_H__

