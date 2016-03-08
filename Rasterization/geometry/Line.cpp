#include "Line.h"
#include "../math/Math.h"

Line2D::Line2D(const Vec2 &p1, const Vec2 &p2)
:begin(p1)
,end(p2)
{
    direction = end - begin;
}

Vec2 Line2D::compute(float t) const {
    if(t > 1)
       t = 1;
    else if(t < 0)
       t = 0;

    return begin + direction * t;
}

LineIntersect Line2D::intersect(const Line2D &p2, float *t1, float *t2) {
    float det = direction.x * p2.direction.y - direction.y * p2.direction.x;
    if(fabs(det) <= EPSLION_E5)
        return LINE_NO_INTERSECT;

    *t1 = (p2.direction.x * (begin.y - p2.begin.y) - p2.direction.y * (begin.x - p2.begin.x)) / det;
    *t2 = (direction.x * (begin.y - p2.begin.y) - direction.y * (begin.x - p2.begin.x)) / det;

    if(*t1 <= 1 && *t1 >= 0 && *t2 <= 1 && *t2 >= 0)
    {
        return LINE_IN_INTERSECT_SEGMENT;
    }

    return LINT_OUT_INTERSECT_SEGMENT;
}

Vec2 Line2D::intersect(const Line2D &p2) {
    float t1 = 0.0f;
    float t2 = 0.0f;
    LineIntersect type = intersect(p2, &t1, &t2);
    if(type == LINE_IN_INTERSECT_SEGMENT)
    {
        return compute(t1);
    }

    return Vec2::ZERO;
}

Line3D::Line3D(const Vec3 &p1, const Vec3 &p2)
:begin(p1)
,end(p2)
{
    direction = end - begin;
}


Vec3 Line3D::compute(float t) const {
    if(t > 1)
        t = 1;
    else if(t < 0)
        t = 0;

    return begin + direction * t;
}

LineIntersect Line3D::intersect(const Line3D &p2, float *t1, float *t2) {
    float det = direction.x * p2.direction.y - direction.y * p2.direction.x;
    if(fabs(det) <= EPSLION_E5)
        return LINE_NO_INTERSECT;

    *t1 = (p2.direction.x * (begin.y - p2.begin.y) - p2.direction.y * (begin.x - p2.begin.x)) / det;
    *t2 = (direction.x * (begin.y - p2.begin.y) - direction.y * (begin.x - p2.begin.x)) / det;

    if(*t1 <= 1 && *t1 >= 0 && *t2 <= 1 && *t2 >= 0)
    {
        return LINE_IN_INTERSECT_SEGMENT;
    }

    return LINT_OUT_INTERSECT_SEGMENT;
}

Vec3 Line3D::intersect(const Line3D &p2) {
    float t1 = 0.0f;
    float t2 = 0.0f;
    LineIntersect type = intersect(p2, &t1, &t2);
    if(type == LINE_IN_INTERSECT_SEGMENT)
    {
        return compute(t1);
    }

    return Vec3::ZERO;
}
