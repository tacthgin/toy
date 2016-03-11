#ifndef _RENDER_H_
#define _RENDER_H_

#include "../geometry/Poly.h"
#include "Matrix4d.h"
#include "../geometry/Object4D.h"
#include "../geometry/Camera.h"
#include "Draw.h"

class Camera;
class Render
{
public:
    Render();
    void clear();
    void transform(const Mat4& m, CoordSelect select);
    void localToWorld(const Vec4& worldPos, CoordSelect select = TRANSFORM_LOCAL_TO_TRANS);
    void worldToCamera(const Camera *camera);
    void cameraToPerspective(const Camera *camera);
    void perspectiveToScreen(const Camera *camera);
    void cameraToScreen(const Camera *camera);

    void convertFromHomogeneous();
    void removeBackfaces(const Camera* camera);

    bool insert(const PolyFace4D* poly);
    bool insert(const Poly4D *poly);
    bool insert(Object4D *obj, bool localVertex = false);

    void drawLine(Draw& draw);
    void drawTriangleSolider(Draw& draw);
    void cocoDrawLine(Draw& draw);
    void cocoDrawTriangle(Draw& draw);
    void drawCall(const Camera *camera, Draw& draw);
    
    int _state;
    int _attr;

    std::vector<PolyFace4D*> _polyList;
    std::vector<PolyFace4D> _polyData;
};


#endif //_RENDER_H_



