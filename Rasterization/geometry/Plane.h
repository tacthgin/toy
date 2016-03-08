#ifndef _PLANE_H_
#define _PLANE_H_

#include "Line.h"

class Vec3;
class Line3D;
class Plane
{
public:
    Plane();
	Plane(const Vec3& pt, const Vec3& n,  bool normalize = true);
    float computePointInPalne(const Vec3& pt);
    LineIntersect intersect(const Line3D& line, float *t, Vec3& pt);

	Vec3 normal;
	Vec3 p;
};

#endif