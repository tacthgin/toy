#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "Vector2d.h"
#include "Vector4d.h"

class Vertex
{
public:
    Vertex();
    union
    {
        struct
        {
            float x, y, z, w;
            float nx, ny, nz, nw;
            float u0, v0;
            
            float i;
            int attr;
        };
        
        struct
        {
            Vec4 v; //顶点
            Vec4 n; //顶点法线
            Vec2 t;//纹理坐标
        };
    };
};

#endif /* _VERTEX_H_ */
