#ifndef __VECTOR_3D_H__
#define __VECTOR_3D_H__


class Vector3d
{
public:
    Vector3d();
	Vector3d(float xx, float yy, float zz);
	Vector3d(const Vector3d& p1, const Vector3d& p2);

	Vector3d operator+(const Vector3d& v) const;
	Vector3d operator-(const Vector3d& v) const;
	float operator*(const Vector3d& v) const;
	Vector3d operator*(float s) const;
    Vector3d operator/(float s) const;

    Vector3d& operator+=(const Vector3d& v);
    Vector3d& operator-=(const Vector3d& v);
    Vector3d& operator*=(float s);
    Vector3d& operator/=(float s);

    bool operator==(const Vector3d& v);
    bool operator!=(const Vector3d& v);

	Vector3d cross(const Vector3d& v);
	float length() const;
	void normalize();
	float cosTh(const Vector3d& v);
	const static Vector3d ZERO;
	float x, y, z;
};

#endif //__VECTOR_3D_H__

