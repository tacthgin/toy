#ifndef _VEC4_H_
#define _VEC4_H_

class Vec4
{
public:
    Vec4();
	Vec4(float xx, float yy, float zz, float ww);
	Vec4(const Vec4& p1, const Vec4& p2);

	Vec4 operator+(const Vec4& v) const;
	Vec4 operator-(const Vec4& v) const;
	float operator*(const Vec4& v) const;
	Vec4 operator*(float s) const;
    Vec4 operator/(float s) const;

    Vec4& operator+=(const Vec4& v);
    Vec4& operator-=(const Vec4& v);
    Vec4& operator*=(const Vec4& v);
    Vec4& operator*=(float s);
    Vec4& operator/=(float s);

    bool operator==(const Vec4& v);
    bool operator!=(const Vec4& v);

	Vec4 cross(const Vec4& v);
	float length() const;
	void normalize();
	float cosTh(const Vec4& v);
    void convertFromHomogenous();

	const static Vec4 ZERO;
	float x, y, z, w;
};

#endif //_VEC4_H_

