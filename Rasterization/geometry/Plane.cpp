#include "Plane.h"
#include "../math/Math.h"

Plane::Plane() {

}

Plane::Plane(const Vec3 &pt, const Vec3 &n, bool normalize)
:p(pt),normal(n)
{
    if(normalize)
    {
        normalize /= sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
    }
}

float Plane::computePointInPalne(const Vec3 &pt) {
    float hs = normal.x * (pt.x - p.x) + normal.y * (pt.y - p.y) + normal.z * (pt.z - p.z);
    return hs;
}

LineIntersect Plane::intersect(const Line3D &line, float *t, Vec3 &pt) {
    float f = line.direction * normal;
    if (fabs(f) <= EPSLION_E5)//表示平行平面
    {
        if (fabs(computePointInPalne(line.begin)) <= EPSLION_E5)//点在平面上
        {
            return LINE_IN_INTERSECT_EVERYWHERE;
        }else
        {
            return LINE_NO_INTERSECT;
        }
    }

    *t = -(normal.x * line.begin.x + normal.y * line.begin.y + normal.z * line.begin.z
         - normal.x * p.x - normal.y * p.y - normal.z * p.z) / f;

    pt = line.compute(*t);

    if(*t <= 1 && *t >= 0)
        return LINE_IN_INTERSECT_SEGMENT;

    return LINT_OUT_INTERSECT_SEGMENT;
}


