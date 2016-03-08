#include "Vertex.h"

Vertex::Vertex()
{
    v = Vec4(0, 0, 0, 1);
    n = Vec4::ZERO;
    t = Vec2::ZERO;
    i = 0.0f;
    attr = 0;
}