#include "Camera.h"
#include "../math/Math.h"

Camera::Camera() {

}

Camera::Camera(Camera::CameraType t, const Vec4 &p, const Vec4 &d, const Vec4 &uvnTarget, float nearZ, float farZ,
               float fovAngle, float width, float height)
:_type(t)
,_pos(p)
,_direction(d)
,_target(uvnTarget)
,_nearClipZ(nearZ)
,_farClipZ(farZ)
,_fov(fovAngle)
,_viewportWidth(width)
,_viewportHeight(height)
,u(Vec4(1, 0, 0, 0))
,v(Vec4(0, 1, 0, 0))
,n(Vec4(0, 0, 1, 0))
,_worldToCam(Mat4::IDENTITY)
,_camToProj(Mat4::IDENTITY)
,_projToView(Mat4::IDENTITY)
{
    _viewportCenterX = (_viewportWidth - 1) / 2;
    _viewportCenterY = (_viewportHeight - 1) / 2;
    _aspectRadio = _viewportWidth / _viewportHeight;

    _viewPlaneWidth = 2;
    _viewPlaneHeight = 2/_aspectRadio;

    float tanFovDiv2 = tan(DEG_TO_RAD(_fov / 2));
    _viewDishH = _viewDish = 0.5 * _viewPlaneWidth * tanFovDiv2;
    _viewDishV = 0.5 * _viewPlaneHeight * tanFovDiv2;

    if (_fov == 90.0)
    {
        _rightClipPlane.normal = Vec3(1, 0, -1);
        _leftClipPlane.normal = Vec3(-1, 0, -1);
        _upClipPlane.normal = Vec3(0, 1, -1);
        _downClipPlane.normal = Vec3(0, -1, -1);
    }else
    {
        _rightClipPlane.normal = Vec3(_viewDish, 0, -_viewPlaneWidth / 2);
        _leftClipPlane.normal = Vec3(-_viewDish, 0, -_viewPlaneWidth / 2);
        _upClipPlane.normal = Vec3(0, _viewDish, -_viewPlaneWidth / 2);
        _downClipPlane.normal = Vec3(0, -_viewDish, -_viewPlaneWidth / 2);
    }
}

void Camera::createEluerMatrix(Camera::CamerarRotate rotate) {
    Mat4 t(1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 1, 0,
               -_pos.x, -_pos.y, -_pos.z, 1);

    float thetaX = _direction.x;
    float thetaY = _direction.y;
    float thetaZ = _direction.z;

    float cosTheta = cos(thetaX);
    float sinTheta = -sin(thetaX);

    Mat4 rx(1, 0, 0, 0,
            0, cosTheta, sinTheta, 0,
            0, -sinTheta, cosTheta, 0,
            0, 0, 0, 1);

    cosTheta = cos(thetaY);
    sinTheta = -sin(thetaY);

    Mat4 ry(cosTheta, 0, -sinTheta, 0,
            0, 1, 0, 0,
            sinTheta, 0, cosTheta, 0,
            0, 0, 0, 1);

    cosTheta = cos(thetaZ);
    sinTheta = -sin(thetaZ);

    Mat4 rz(cosTheta, sinTheta, 0, 0,
            -sinTheta, cosTheta, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    Mat4 temp;
    switch (rotate)
    {
        case CAMERA_ROTATE_XYZ:
        {
            temp = rx * ry * rz;
        }break;

        case CAMERA_ROTATE_XZY:
        {
            temp = rx * rz * ry;
        }break;

        case CAMERA_ROTATE_YXZ:
        {
            temp = ry * rx * rz;
        }break;

        case CAMERA_ROTATE_YZX:
        {
            temp = ry * rz * rx;
        }break;

        case CAMERA_ROTATE_ZXY:
        {
            temp = rz * rx * ry;
        }break;

        case CAMERA_ROTATE_ZYX:
        {
            temp = rz * ry * rx;
        }break;
    }

    _worldToCam =  t * temp;
}

void Camera::createUVNMatrix(Camera::UVNMode mode) {
    Mat4 t(1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           -_pos.x, -_pos.y, -_pos.z, 1);

    if(mode == UVN_MODE_SPHERICAL)
    {
        float phi = _direction.x; //仰角
        float theta = _direction.y;//方位角

        float sinPhi = sin(phi);
        float cosPhi = cos(phi);

        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        _target.x = -sinPhi * sinTheta;
        _target.y = cosPhi;
        _target.z = sinPhi * cosTheta;
    }

    n = Vec4(_pos, _target);
    v = Vec4(0, 1, 0, 0);
    u = v.cross(n);
    v = n.cross(u);

    u.normalize();
    v.normalize();
    n.normalize();

    Mat4 r(u.x, v.x, n.x, 0,
           u.y, v.y, n.y, 0,
           u.z, v.z, n.z, 0,
           0, 0, 0, 1);

    _worldToCam = t * r;
}

void Camera::createPrespectiveMatrix() {
    _camToProj.set(_viewDishH, 0, 0, 0,
                0, _viewDishV * _aspectRadio, 0, 0,
                0, 0, 1, 1,
                0, 0, 0, 0);
}

void Camera::createScreenMatrix() {
    float alpha = 0.5 * _viewportWidth - 0.5;
    float beta = 0.5 * _viewportHeight - 0.5;

    _projToView.set(alpha, 0, 0, 0,
                   0, -beta, 0, 0,
                   alpha, beta, 1, 0,
                   0, 0, 0, 1);
}
