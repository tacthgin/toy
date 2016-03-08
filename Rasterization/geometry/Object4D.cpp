#include "Object4D.h"
#include "Camera.h"
#include "../render/Draw.h"
#include "../math/Math.h"

Object4D::Object4D()
:_id(0)
,_state(0)
,_attr(0)
,_frameNums(0)
,_curFrame(0)
,_mati(0)
,_avgRadius(nullptr)
,_maxRadius(nullptr)
{
     clear();
}

void Object4D::init(int vertexNums, int polyNums, int frameNums)
{
    clear();
    _vlist.resize(vertexNums);
    _tvlist.resize(vertexNums);
    _polyList.resize(polyNums);
    
    _maxRadius = new float[frameNums];
    _avgRadius = new float[frameNums];
}

void Object4D::clear()
{
    if (_avgRadius) {
        delete [] _avgRadius;
        _avgRadius = nullptr;
    }
    
    if (_maxRadius) {
        delete [] _maxRadius;
        _maxRadius = nullptr;
    }
}

void Object4D::reset() {
    RESET_BIT(_state, OBJECT4D_STATE_CULLED);
    for (auto& poly : _polyList) {
        if(!(poly._state & POLY4D_STATE_ACTIVE))
            continue;
        
        RESET_BIT(poly._state, POLY4D_STATE_CLIPPED);
        RESET_BIT(poly._state, POLY4D_STATE_BACKFACE);
    }
}

void Object4D::transform(const Mat4 &m, CoordSelect select, bool transfromBasis, bool allFrames) {
    if(select != TRANSFORM_LOCAL_ONLY && _tvlist.empty())
    {
        std::copy(_vlist.begin(), _vlist.end(), std::back_inserter(_tvlist));
    }
    
    switch (select)
    {
        case TRANSFORM_LOCAL_ONLY:
        {
            for (size_t vertex = 0; vertex < _vlist.size(); ++vertex) {
                _vlist[vertex].v = _vlist[vertex].v * m;
            }
        }break;

        case TRANSFORM_TRANS_ONLY:
        {
            for (size_t vertex = 0; vertex < _tvlist.size(); ++vertex) {
                _tvlist[vertex].v = _tvlist[vertex].v * m;
            }
        }break;

        case TRANSFORM_LOCAL_TO_TRANS:
        {
            for (size_t vertex = 0; vertex < _vlist.size(); ++vertex) {
                _tvlist[vertex].v = _vlist[vertex].v * m;
            }
        }break;

        default:
            break;
    }

    if(transfromBasis)
    {
        _ux = _ux * m;
        _uy = _uy * m;
        _uz = _uz * m;
    }
}

void Object4D::localToWorld(CoordSelect select, bool allFrames) {
    if(_tvlist.empty())
    {
        std::copy(_vlist.begin(), _vlist.end(), std::back_inserter(_tvlist));
    }

    if(select == TRANSFORM_LOCAL_TO_TRANS)
    {
        for (size_t vertex = 0; vertex < _vlist.size(); ++vertex) {
            _tvlist[vertex].v = _vlist[vertex].v + _worldPos;
        }
    }else//TRANSFORM_TRANS_ONLY
    {

        for (size_t vertex = 0; vertex < _vlist.size(); ++vertex) {
            _tvlist[vertex].v += _worldPos;
        }
    }
}

void Object4D::worldToCamera(const Camera *camera)
{
    for (auto& vertex : _tvlist) {
        vertex.v = vertex.v * camera->_worldToCam;
    }
}

void Object4D::cameraToPerspective(const Camera *camera) {
    for (auto &vertex : _tvlist) {
        vertex.x = camera->_viewDish * vertex.x / vertex.z;
        vertex.y = camera->_viewDish * vertex.y / vertex.z;
    }
}

void Object4D::perspectiveToScreen(const Camera *camera) {
    float alpha = 0.5 * camera->_viewportWidth - 0.5;
    float beta = 0.5 * camera->_viewportHeight - 0.5;

    for (auto &vertex : _tvlist ) {
        vertex.x = alpha * vertex.x + alpha;
        vertex.y = -beta * vertex.y + beta;
    }
}

void Object4D::cameraToScreen(const Camera *camera) {
    float alpha = 0.5 * camera->_viewportWidth - 0.5;
    float beta = 0.5 * camera->_viewportHeight - 0.5;

    for (auto &vertex : _tvlist ) {
        vertex.x = camera->_viewDish * vertex.x / vertex.z;
        vertex.y = camera->_viewDish * vertex.y / vertex.z;
        //screen
        vertex.x = alpha * vertex.x + alpha;
        vertex.y = beta * vertex.y + beta;
    }
}

bool Object4D::objectCull(const Camera *camera, int cullFlag) {
    Vec4 spherePos = _worldPos * camera->_worldToCam;
    if(cullFlag & CULL_OBJECT_Z_PLANE)
    {
        if(spherePos.z - _maxRadius[_curFrame] > camera->_farClipZ || spherePos.z + _maxRadius[_curFrame] < camera->_nearClipZ )
        {
            SET_BIT(_state, OBJECT4D_STATE_CULLED);
            return true;
        }
    }

    if(cullFlag & CULL_OBJECT_X_PLANE)
    {
        float zText = camera->_viewPlaneWidth * 0.5f * spherePos.z / camera->_viewDish;
        if(spherePos.x - _maxRadius[_curFrame] > zText || spherePos.x + _maxRadius[_curFrame] < -zText)
        {
            SET_BIT(_state, OBJECT4D_STATE_CULLED);
            return  true;
        }
    }

    if(cullFlag & CULL_OBJCET_Y_PLANE)
    {
        float zText = camera->_viewPlaneHeight * 0.5f * spherePos.z / camera->_viewDish;
        if(spherePos.y - _maxRadius[_curFrame] > zText || spherePos.y + _maxRadius[_curFrame] < -zText)
        {
            SET_BIT(_state, OBJECT4D_STATE_CULLED);
            return  true;
        }
    }

    return false;
}

void Object4D::removeBackfaces(const Camera *camera) {
    if(_state & OBJECT4D_STATE_CULLED)
    {
        return;
    }
    
    for (auto& curPoly : _polyList) {
        if(!(curPoly._state & POLY4D_STATE_ACTIVE) ||
           (curPoly._state & POLY4D_STATE_CLIPPED) ||
           (curPoly._state & POLY4D_STATE_BACKFACE) ||
           (curPoly._attr & POLY4D_ATTR_2SIDE))
            continue;
        
        Vec4 u(_tvlist[curPoly._vindex[0]].v, _tvlist[curPoly._vindex[1]].v);
        Vec4 v(_tvlist[curPoly._vindex[0]].v, _tvlist[curPoly._vindex[2]].v);
        
        Vec4 n = u.cross(v);
        
        //创建指向视点的坐标
        Vec4 view(_tvlist[curPoly._vindex[0]].v, camera->_pos);
        
        float dp = n * view;
        if (std::abs(dp) < EPSLION_E5 || dp < 0) {
            SET_BIT(curPoly._state, POLY4D_STATE_BACKFACE);
        }
    }
}

void Object4D::computeRadius() {
    float curR = 0.0f;
    for (auto& v : _vlist) {
        if((curR = v.x * v.x + v.y * v.y + v.z * v.z) > _maxRadius[_curFrame])
        {
            _maxRadius[_curFrame] = curR;
        }
    }

    _maxRadius[_curFrame] = std::sqrt(_maxRadius[_curFrame]);
}

void Object4D::computePolyNormals()
{
    for (auto& poly : _polyList) {
        int vi0 = poly._vindex[0];
        int vi1 = poly._vindex[1];
        int vi2 = poly._vindex[2];
        
        Vec4 u(_vlist[vi0].v, _vlist[vi1].v);
        Vec4 v(_vlist[vi0].v, _vlist[vi2].v);
        Vec4 n = u.cross(v);
        
        poly._nLength = n.length();
    }
}

void Object4D::computeVertexNormals()
{
    std::map<int, int> vertexNormal;
    
    for (auto& poly : _polyList)
    {
        if (poly._attr & POLY4D_ATTR_SHADE_MODE_GOURAUD)
        {
            int vi0 = poly._vindex[0];
            int vi1 = poly._vindex[1];
            int vi2 = poly._vindex[2];
            
            Vec4 u(_vlist[vi0].v, _vlist[vi1].v);
            Vec4 v(_vlist[vi0].v, _vlist[vi2].v);
            
            Vec4 n = u.cross(v);
            
            _vlist[vi0].n = n;
            _vlist[vi1].n = n;
            _vlist[vi2].n = n;
            
            vertexNormal[vi0] += 1;
            vertexNormal[vi1] += 1;
            vertexNormal[vi2] += 1;
        }
    }
    
    for (auto i = 0; i < _vlist.size(); ++i) {
        if (vertexNormal.find(i) != vertexNormal.end()) {
            _vlist[i].n /= vertexNormal[i];
            _vlist[i].n.normalize();
        }
    }
}

void Object4D::drawLine(Draw& draw) {
    for (auto &poly : _polyList) {
        if(!(poly._state & POLY4D_STATE_ACTIVE) ||
           (poly._state & POLY4D_STATE_CLIPPED) ||
           (poly._state & POLY4D_STATE_BACKFACE))
            continue;

        int vindex0 = poly._vindex[0];
        int vindex1 = poly._vindex[1];
        int vindex2 = poly._vindex[2];

        draw.drawLine(_tvlist[vindex0].x,
                        _tvlist[vindex0].y,
                        _tvlist[vindex1].x,
                        _tvlist[vindex1].y,
                        poly._color, poly._color);

        draw.drawLine(_tvlist[vindex1].x,
                         _tvlist[vindex1].y,
                         _tvlist[vindex2].x,
                         _tvlist[vindex2].y,
                         poly._color, poly._color);

        draw.drawLine(_tvlist[vindex2].x,
                         _tvlist[vindex2].y,
                         _tvlist[vindex0].x,
                         _tvlist[vindex0].y,
                         poly._color, poly._color);
    }
}

void Object4D::drawTriangleSolider(Draw& draw)
{
    for (auto &poly : _polyList) {
        if(!(poly._state & POLY4D_STATE_ACTIVE) ||
           (poly._state & POLY4D_STATE_CLIPPED) ||
           (poly._state & POLY4D_STATE_BACKFACE))
            continue;
        
        int vindex0 = poly._vindex[0];
        int vindex1 = poly._vindex[1];
        int vindex2 = poly._vindex[2];
        
        draw.drawTriangle(_tvlist[vindex0].x, _tvlist[vindex0].y,
                          _tvlist[vindex1].x, _tvlist[vindex1].y,
                          _tvlist[vindex2].x, _tvlist[vindex2].y, poly._color);
    }

}

void Object4D::cocoDrawLine(Draw& draw)
{
    for (auto &poly : _polyList) {
        if(!(poly._state & POLY4D_STATE_ACTIVE) ||
           (poly._state & POLY4D_STATE_CLIPPED) ||
           (poly._state & POLY4D_STATE_BACKFACE))
            continue;
        
        int vindex0 = poly._vindex[0];
        int vindex1 = poly._vindex[1];
        int vindex2 = poly._vindex[2];
        
        draw.cocoDrawLine(_tvlist[vindex0].x,
                      _tvlist[vindex0].y,
                      _tvlist[vindex1].x,
                      _tvlist[vindex1].y,
                      poly._color, poly._color);
        
        draw.cocoDrawLine(_tvlist[vindex1].x,
                      _tvlist[vindex1].y,
                      _tvlist[vindex2].x,
                      _tvlist[vindex2].y,
                      poly._color, poly._color);
        
        draw.cocoDrawLine(_tvlist[vindex2].x,
                      _tvlist[vindex2].y,
                      _tvlist[vindex0].x,
                      _tvlist[vindex0].y,
                      poly._color, poly._color);
    }

}

void Object4D::cocoDrawTriangle(Draw& draw)
{
    for (auto &poly : _polyList) {
        if(!(poly._state & POLY4D_STATE_ACTIVE) ||
           (poly._state & POLY4D_STATE_CLIPPED) ||
           (poly._state & POLY4D_STATE_BACKFACE))
            continue;
        
        int vindex0 = poly._vindex[0];
        int vindex1 = poly._vindex[1];
        int vindex2 = poly._vindex[2];
        
        draw.cocoDrawTriangle(_tvlist[vindex0].x,
                          _tvlist[vindex0].y,
                          _tvlist[vindex1].x,
                          _tvlist[vindex1].y,
                          _tvlist[vindex2].x,
                          _tvlist[vindex2].y,
                          poly._color);
    }
}

void Object4D::drawCall(const Camera *camera, Draw& draw)
{
    reset();
    localToWorld(TRANSFORM_TRANS_ONLY);
    worldToCamera(camera);
    if(objectCull(camera, CULL_OBJECT_XYZ_PLANES))
    {
        return;
    }
    removeBackfaces(camera);
    cameraToScreen(camera);
    cocoDrawTriangle(draw);
}

bool Object4D::setFrame(int frame)
{
    if(!(this->_attr & OBJECT4D_ATTR_MULTI_FRAME))
    {
        return false;
    }
    
    if (frame < 0) {
        frame = 0;
    }else if(frame >= _frameNums)
    {
        frame = _frameNums - 1;
    }
    
    this->_curFrame = frame;
    
    return true;
}



