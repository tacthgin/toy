#include "Render.h"
#include "Draw.h"
#include "../math/Math.h"
#include "../geometry/Geometry.h"
#include "cocos2d.h"

Render::Render()
:_state(0)
,_attr(0)
{

}

void Render::clear()
{
    _state = 0;
    _attr = 0;
    _polyList.clear();
    _polyData.clear();
}

void Render::transform(const Mat4 &m, CoordSelect select) {
    switch (select)
    {
        case TRANSFORM_LOCAL_ONLY:
        {
            for (auto curPoly : _polyList) {
                if (curPoly == nullptr ||
                    !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
                    (curPoly->_state & POLY4D_STATE_CLIPPED) ||
                    (curPoly->_state & POLY4D_STATE_BACKFACE)) {
                    continue;
                }

                for (int vertex = 0; vertex < 3; ++vertex) {
                    curPoly->_vlist[vertex].v = curPoly->_vlist[vertex].v * m;
                }
            }
        }break;

        case TRANSFORM_TRANS_ONLY:
        {
            for (auto curPoly : _polyList) {
                if (curPoly == nullptr ||
                    !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
                    (curPoly->_state & POLY4D_STATE_CLIPPED) ||
                    (curPoly->_state & POLY4D_STATE_BACKFACE)) {
                    continue;
                }

                for (int vertex = 0; vertex < 3; ++vertex) {
                    curPoly->_tvlist[vertex].v =  curPoly->_tvlist[vertex].v * m;
                }
            }
        }break;

        case TRANSFORM_LOCAL_TO_TRANS:
        {
            for (auto curPoly : _polyList) {
                if (curPoly == nullptr ||
                    !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
                    (curPoly->_state & POLY4D_STATE_CLIPPED) ||
                    (curPoly->_state & POLY4D_STATE_BACKFACE)) {
                    continue;
                }

                for (int vertex = 0; vertex < 3; ++vertex) {
                    curPoly->_tvlist[vertex].v = curPoly->_vlist[vertex].v * m;
                }
            }
        }break;
        default:
            break;
    }
}

void Render::localToWorld(const Vec4& worldPos, CoordSelect select) {
    if(select == TRANSFORM_LOCAL_TO_TRANS)
    {
        for (auto curPoly : _polyList) {
            if (curPoly == nullptr ||
                !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
                (curPoly->_state & POLY4D_STATE_CLIPPED) ||
                (curPoly->_state & POLY4D_STATE_BACKFACE)) {
                continue;
            }

            for (int vertex = 0; vertex < 3; ++vertex) {
                curPoly->_tvlist[vertex].v = curPoly->_vlist[vertex].v + worldPos;
            }
        }
    }else//TRANSFORM_TRANS_ONLY
    {
        for (auto curPoly : _polyList) {
            if (curPoly == nullptr ||
                !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
                (curPoly->_state & POLY4D_STATE_CLIPPED) ||
                (curPoly->_state & POLY4D_STATE_BACKFACE)) {
                continue;
            }

            for (int vertex = 0; vertex < 3; ++vertex) {
                curPoly->_tvlist[vertex].v += worldPos;
            }
        }
    }
}

void Render::worldToCamera(const Camera *camera) {
    for (auto curPoly : _polyList) {
        if (curPoly == nullptr ||
            !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
            (curPoly->_state & POLY4D_STATE_CLIPPED) ||
            (curPoly->_state & POLY4D_STATE_BACKFACE)) {
            continue;
        }
        
        for (auto& vertex : curPoly->_tvlist) {
            vertex.v = vertex.v * camera->_worldToCam;
        }
    }
}

void Render::cameraToPerspective(const Camera *camera) {
    for (auto curPoly : _polyList) {
        if (curPoly == nullptr ||
            !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
            (curPoly->_state & POLY4D_STATE_CLIPPED) ||
            (curPoly->_state & POLY4D_STATE_BACKFACE)) {
            continue;
        }

        for (int vertex = 0; vertex < 3; ++vertex) {
            float z = curPoly->_tvlist[vertex].z;
            curPoly->_tvlist[vertex].x = camera->_viewDish * curPoly->_tvlist[vertex].x / z;
            curPoly->_tvlist[vertex].y = camera->_viewDish * curPoly->_tvlist[vertex].y / z;
        }
    }
}

void Render::perspectiveToScreen(const Camera *camera) {

    float alpha = 0.5 * camera->_viewportWidth - 0.5;
    float beta = 0.5 * camera->_viewportHeight - 0.5;

    for (auto curPoly : _polyList) {
        if (curPoly == nullptr ||
            !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
            (curPoly->_state & POLY4D_STATE_CLIPPED) ||
            (curPoly->_state & POLY4D_STATE_BACKFACE)) {
            continue;
        }

        for (int vertex = 0; vertex < 3; ++vertex) {
            curPoly->_tvlist[vertex].v.x = alpha * curPoly->_tvlist[vertex].x + alpha;
            curPoly->_tvlist[vertex].v.y = -beta * curPoly->_tvlist[vertex].y + beta;
        }
    }
}

void Render::cameraToScreen(const Camera *camera) {

    float alpha = 0.5 * camera->_viewportWidth - 0.5;
    float beta = 0.5 * camera->_viewportHeight - 0.5;

    for (auto curPoly : _polyList) {
        if (curPoly == nullptr ||
            !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
            (curPoly->_state & POLY4D_STATE_CLIPPED) ||
            (curPoly->_state & POLY4D_STATE_BACKFACE)) {
            continue;
        }
        
        for (auto& vertex : curPoly->_tvlist) {
            vertex.x = camera->_viewDish * vertex.x / vertex.z;
            vertex.y = camera->_viewDish * vertex.y / vertex.z;
            
            vertex.x = alpha * vertex.x + alpha;
            vertex.y = beta * vertex.y + beta;
        }
    }
}

void Render::convertFromHomogeneous() {
    for (auto curPoly : _polyList) {
        if (curPoly == nullptr ||
            !(curPoly->_state & POLY4D_STATE_ACTIVE) ||
            (curPoly->_state & POLY4D_STATE_CLIPPED) ||
            (curPoly->_state & POLY4D_STATE_BACKFACE)) {
            continue;
        }

        for (int vertex = 0; vertex < 3; ++vertex) {
            curPoly->_tvlist[vertex].v.convertFromHomogenous();
        }
    }
}

void Render::removeBackfaces(const Camera *camera) {
    for (auto &curPoly : _polyList) {
        if(!(curPoly->_state & POLY4D_STATE_ACTIVE) ||
           (curPoly->_state & POLY4D_STATE_CLIPPED) ||
           (curPoly->_state & POLY4D_STATE_BACKFACE) ||
           (curPoly->_attr & POLY4D_ATTR_2SIDE))
            continue;

        Vec4 u(curPoly->_tvlist[0].v, curPoly->_tvlist[1].v);
        Vec4 v(curPoly->_tvlist[0].v, curPoly->_tvlist[2].v);

        Vec4 n = u.cross(v);

        //创建指向视点的坐标
        Vec4 view(curPoly->_tvlist[0].v, camera->_pos);

        float dp = n * view;
        if (std::abs(dp) < EPSLION_E5 || dp < 0)
        {
            SET_BIT(curPoly->_state, POLY4D_STATE_BACKFACE);
        }
    }
}

bool Render::insert(const PolyFace4D* poly) {
    _polyData.push_back(*poly);
    _polyList.clear();
    for(auto& poly : _polyData)
    {
        _polyList.push_back(&poly);
    }
    return true;
}

bool Render::insert(const Poly4D *poly)
{
    PolyFace4D pf;
    pf._state = poly->_state;
    pf._attr = poly->_attr;
    pf._color = poly->_color;
    for (int i = 0; i < 3; ++i) {
        pf._tvlist[i] = (*poly->_vlist)[poly->_vindex[i]];
    }
    
    insert(&pf);
    return true;
}

bool Render::insert(Object4D *obj, bool localVertex)
{
    if (!(obj->_state & OBJECT4D_STATE_ACTIVE) ||
        (obj->_state & OBJECT4D_STATE_CULLED) ||
        !(obj->_state & OBJECT4D_STATE_VISIBLE))
        return false;
    
    for (auto &poly : obj->_polyList) {
        if (!(poly._state & POLY4D_STATE_ACTIVE) ||
            (poly._state & POLY4D_STATE_CLIPPED ) ||
            (poly._state & POLY4D_STATE_BACKFACE) )
            continue; // move onto next poly
        
        if (localVertex) {
            poly._vlist = &(obj->_vlist);
        }else
        {
            poly._vlist = &(obj->_tvlist);
        }
        
        insert(&poly);
    }
    
    return true;
}

void Render::drawLine( Draw& draw) {
    for (auto& poly : _polyList) {
        if(!(poly->_state & POLY4D_STATE_ACTIVE) ||
           (poly->_state & POLY4D_STATE_CLIPPED) ||
           (poly->_state & POLY4D_STATE_BACKFACE))
            continue;

        draw.drawLine(poly->_tvlist[0].x,
                         poly->_tvlist[0].y,
                         poly->_tvlist[1].x,
                         poly->_tvlist[1].y,
                         poly->_color, poly->_color);

        draw.drawLine(poly->_tvlist[1].x,
                         poly->_tvlist[1].y,
                         poly->_tvlist[2].x,
                         poly->_tvlist[2].y,
                         poly->_color, poly->_color);

        draw.drawLine(poly->_tvlist[2].x,
                         poly->_tvlist[2].y,
                         poly->_tvlist[0].x,
                         poly->_tvlist[0].y,
                         poly->_color, poly->_color);
    }
}

void Render::drawTriangleSolider(Draw& draw)
{
    for (auto &poly : _polyList) {
        if(!(poly->_state & POLY4D_STATE_ACTIVE) ||
           (poly->_state & POLY4D_STATE_CLIPPED) ||
           (poly->_state & POLY4D_STATE_BACKFACE))
            continue;
        
        draw.drawTriangle(poly->_tvlist[0].x, poly->_tvlist[0].y,
                          poly->_tvlist[1].x, poly->_tvlist[1].y,
                          poly->_tvlist[2].x, poly->_tvlist[2].y, poly->_color);
    }
}

void Render::cocoDrawLine(Draw& draw)
{
    for (auto& poly : _polyList) {
        if(!(poly->_state & POLY4D_STATE_ACTIVE) ||
           (poly->_state & POLY4D_STATE_CLIPPED) ||
           (poly->_state & POLY4D_STATE_BACKFACE))
            continue;
        poly->_color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        draw.cocoDrawLine(poly->_tvlist[0].x,
                          poly->_tvlist[0].y,
                          poly->_tvlist[1].x,
                          poly->_tvlist[1].y,
                          poly->_color, poly->_color);
        
        draw.cocoDrawLine(poly->_tvlist[1].x,
                          poly->_tvlist[1].y,
                          poly->_tvlist[2].x,
                          poly->_tvlist[2].y,
                          poly->_color, poly->_color);
        
        draw.cocoDrawLine(poly->_tvlist[2].x,
                          poly->_tvlist[2].y,
                          poly->_tvlist[0].x,
                          poly->_tvlist[0].y,
                          poly->_color, poly->_color);
    }
}

void Render::cocoDrawTriangle(Draw& draw)
{
    for (auto& poly : _polyList) {
        if(!(poly->_state & POLY4D_STATE_ACTIVE) ||
           (poly->_state & POLY4D_STATE_CLIPPED) ||
           (poly->_state & POLY4D_STATE_BACKFACE))
            continue;
        poly->_color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        
        draw.cocoDrawTriangle(poly->_tvlist[0].x,
                          poly->_tvlist[0].y,
                          poly->_tvlist[1].x,
                          poly->_tvlist[1].y,
                          poly->_tvlist[2].x,
                          poly->_tvlist[2].y,
                          poly->_color);
    }
}

void Render::drawCall(const Camera *camera, Draw& draw)
{
    worldToCamera(camera);
    removeBackfaces(camera);
    cameraToScreen(camera);
    cocoDrawTriangle(draw);
}



