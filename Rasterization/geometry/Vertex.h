//
//  Vertex.h
//  Rasteriza
//
//  Created by 陈起慧 on 15/6/15.
//
//

#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "../math/Vec2.h"
#include "../math/Vec4.h"

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
