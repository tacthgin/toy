#include "Camera.h"
#include "../math/Math.h"

Camera::Camera() {

}

Camera::Camera(Camera::CameraType t, const Vector4d &p, const Vector4d &d, const Vector4d &uvnTarget, float nearZ, float farZ,
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
,u(Vector4d(1, 0, 0, 0))
,v(Vector4d(0, 1, 0, 0))
,n(Vector4d(0, 0, 1, 0))
,_worldToCam(Matrix4d::IDENTITY)
,_camToProj(Matrix4d::IDENTITY)
,_projToView(Matrix4d::IDENTITY)
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
        _rightClipPlane.normal = Vector3d(1, 0, -1);
        _leftClipPlane.normal = Vector3d(-1, 0, -1);
        _upClipPlane.normal = Vector3d(0, 1, -1);
        _downClipPlane.normal = Vector3d(0, -1, -1);
    }else
    {
        _rightClipPlane.normal = Vector3d(_viewDish, 0, -_viewPlaneWidth / 2);
        _leftClipPlane.normal = Vector3d(-_viewDish, 0, -_viewPlaneWidth / 2);
        _upClipPlane.normal = Vector3d(0, _viewDish, -_viewPlaneWidth / 2);
        _downClipPlane.normal = Vector3d(0, -_viewDish, -_viewPlaneWidth / 2);
    }
}

void Camera::createEluerMatrix(Camera::CamerarRotate rotate) {
    Matrix4d t(1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 1, 0,
               -_pos.x, -_pos.y, -_pos.z, 1);

    float thetaX = _direction.x;
    float thetaY = _direction.y;
    float thetaZ = _direction.z;

    float cosTheta = cos(thetaX);
    float sinTheta = -sin(thetaX);

    Matrix4d rx(1, 0, 0, 0,
            0, cosTheta, sinTheta, 0,
            0, -sinTheta, cosTheta, 0,
            0, 0, 0, 1);

    cosTheta = cos(thetaY);
    sinTheta = -sin(thetaY);

    Matrix4d ry(cosTheta, 0, -sinTheta, 0,
            0, 1, 0, 0,
            sinTheta, 0, cosTheta, 0,
            0, 0, 0, 1);

    cosTheta = cos(thetaZ);
    sinTheta = -sin(thetaZ);

    Matrix4d rz(cosTheta, sinTheta, 0, 0,
            -sinTheta, cosTheta, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    Matrix4d temp;
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
    Matrix4d t(1, 0, 0, 0,
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

    n = Vector4d(_pos, _target);
    v = Vector4d(0, 1, 0, 0);
    u = v.cross(n);
    v = n.cross(u);

    u.normalize();
    v.normalize();
    n.normalize();

    Matrix4d r(u.x, v.x, n.x, 0,
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
