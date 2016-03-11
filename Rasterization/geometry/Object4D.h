#ifndef _OBJECT4D_H_
#define _OBJECT4D_H_

#include "Geometry.h"
#include "Poly.h"
#include "../render/Draw.h"
#include "Matrix4d.h"


class Camera;
class Object4D
{
public:
    Object4D();
    void init(int vertexNums, int polyNums, int frameNums);
    void clear();
    void reset();
    
    void translate(const Vec4& pt);//平移物体
    void scale(const Vec4& s, bool allFrames = false);//缩放
    void rotate(float thetaX, float thetaY, float thetaZ, bool allFrames);//旋转
    
    void transform(const Mat4& m, CoordSelect select, bool transfromBasis, bool allFrames = false);
    
    void localToWorld(CoordSelect select = TRANSFORM_LOCAL_TO_TRANS, bool allFrames = false);
    void worldToCamera(const Camera *camera);
    void cameraToPerspective(const Camera *camera);//相机坐标到透视坐标
    void perspectiveToScreen(const Camera *camera);//透视坐标到屏幕坐标
    void cameraToScreen(const Camera *camera);

    bool objectCull(const Camera* camera, int cullFlag);//物体剔除
    void removeBackfaces(const Camera* camera);//背面消除
    
    void computeRadius();
    void computePolyNormals();
    void computeVertexNormals();

    void drawLine( Draw& draw);
    void drawTriangleSolider(Draw& draw);
    
    void cocoDrawLine(Draw& draw);
    void cocoDrawTriangle(Draw& draw);
    
    void drawCall(const Camera *camera, Draw& draw);
    
    bool setFrame(int frame);
    
    int _id;
    char _name[64];
    int _state;
    int _attr;
    int _mati;
    
    float *_avgRadius;//平均半径
    float *_maxRadius;

    Vec4 _worldPos;
    Vec4 _direction;

    Vec4 _ux, _uy, _uz;//局部坐标轴
    
    int _frameNums;
    int _curFrame;

    std::vector<Vertex> _vlist;  //顶点局部坐标
    std::vector<Vertex> _tvlist; //顶点变换后的数组
    
    std::vector<Poly4D> _polyList; //多边形数组
    std::vector<Vec2> _tlist;//纹理坐标列表
};





#endif //_OBJECT4D_H_
