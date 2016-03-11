#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Matrix4d.h"
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
           const Vector4d& p,
           const Vector4d& d,
           const Vector4d& uvnTarget,
           float nearZ,
           float farZ, float fovAngle, float width, float height);
    void createEluerMatrix(CamerarRotate rotate);
    void createUVNMatrix(UVNMode mode);
    void createPrespectiveMatrix();
    void createScreenMatrix();

    int _state;
    CameraType _type;

    Vector4d _pos;//相机位置
    Vector4d _direction;//相机朝向

    Vector4d u;
    Vector4d v;
    Vector4d n; //uvn相机
    Vector4d _target; //uvn模型位置

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

    Matrix4d _worldToCam;//世界坐标到相机坐标
    Matrix4d _camToProj;//相机坐标到投影坐标
    Matrix4d _projToView;//投影坐标到屏幕坐标
};

#endif //__CAMERA_H__
