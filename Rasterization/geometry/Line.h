#ifndef _LINE_H_
#define _LINE_H_ 

#include "../math/Vec2.h"
#include "../math/Vec3.h"

enum LineIntersect
{
    LINE_NO_INTERSECT,
    LINE_IN_INTERSECT_SEGMENT,
    LINT_OUT_INTERSECT_SEGMENT,
    LINE_IN_INTERSECT_EVERYWHERE
};

class Vec2;
class Line2D
{
public:
    Line2D(const Vec2& p1, const Vec2& p2);
    Vec2 compute(float t) const;
    LineIntersect intersect(const Line2D& p2, float *t1, float *t2);
    Vec2 intersect(const Line2D& p2);

    Vec2 begin;
    Vec2 end;
    Vec2 direction;
};

class Vec3;
class Line3D
{
public:
	Line3D(const Vec3& p1, const Vec3& p2);
    Vec3 compute(float t) const;
    LineIntersect intersect(const Line3D& p2, float *t1, float *t2);
    Vec3 intersect(const Line3D& p2);

	Vec3 begin;
	Vec3 end;
	Vec3 direction;
};



#endif