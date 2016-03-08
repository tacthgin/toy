#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../math/Mat4.h"
#include "Plane.h"

class Camera
{
public:
    enum CameraType
    {
        CAMERA_ELUER,
        CAMERA_UVN
    };

    enum CamerarRotate
    {
        CAMERA_ROTATE_XYZ,
        CAMERA_ROTATE_XZY,
        CAMERA_ROTATE_YXZ,
        CAMERA_ROTATE_YZX,
        CAMERA_ROTATE_ZXY,
        CAMERA_ROTATE_ZYX
    };

    enum UVNMode
    {
        UVN_MODE_SIMPLE,
        UVN_MODE_SPHERICAL
    };

    Camera();
    Camera(CameraType t,
           const Vec4& p,
           const Vec4& d,
           const Vec4& uvnTarget,
           float nearZ,
           float farZ, float fovAngle, float width, float height);
    void createEluerMatrix(CamerarRotate rotate);
    void createUVNMatrix(UVNMode mode);
    void createPrespectiveMatrix();
    void createScreenMatrix();

    int _state;
    CameraType _type;

    Vec4 _pos;//相机位置
    Vec4 _direction;//相机朝向

    Vec4 u;
    Vec4 v;
    Vec4 n; //uvn相机
    Vec4 _target; //uvn模型位置

    float _viewDish;//视距
    float _viewDishH;//水平视距
    float _viewDishV;//垂直视距
    float _fov;//视野

    float _nearClipZ;//近裁减面
    float _farClipZ;

    Plane _rightClipPlane;
    Plane _leftClipPlane;
    Plane _upClipPlane;
    Plane _downClipPlane;

    float _viewPlaneWidth;//视平面的宽度和高度
    float _viewPlaneHeight;

    float _viewportWidth; //视口宽高，中心坐标
    float _viewportHeight;
    float _viewportCenterX;
    float _viewportCenterY;

    float _aspectRadio;//宽高比

    Mat4 _worldToCam;//世界坐标到相机坐标
    Mat4 _camToProj;//相机坐标到投影坐标
    Mat4 _projToView;//投影坐标到屏幕坐标
};

#endif //_CAMERA_H_
