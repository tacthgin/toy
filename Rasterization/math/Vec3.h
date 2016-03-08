#ifndef _VEC3_H_
#define _VEC3_H_


class Vec3
{
public:
    Vec3();
	Vec3(float xx, float yy, float zz);
	Vec3(const Vec3& p1, const Vec3& p2);

	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	float operator*(const Vec3& v) const;
	Vec3 operator*(float s) const;
    Vec3 operator/(float s) const;

    Vec3& operator+=(const Vec3& v);
    Vec3& operator-=(const Vec3& v);
    Vec3& operator*=(float s);
    Vec3& operator/=(float s);

    bool operator==(const Vec3& v);
    bool operator!=(const Vec3& v);

	Vec3 cross(const Vec3& v);
	float length() const;
	void normalize();
	float cosTh(const Vec3& v);
	const static Vec3 ZERO;
	float x, y, z;
};

#endif //_VEC3_H_

