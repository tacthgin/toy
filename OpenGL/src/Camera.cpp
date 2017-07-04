#include "Camera.h"

using namespace glm;

Camera::Camera(const glm::vec3 & pos)
:_pos(pos)
,_front(vec3(0.0f, 0.0f, -1.0f))
,_up(vec3(0.0f, 1.0f, 0.0f))
,_ascept(45.0f)
,_sensitivity(0.05f)
, _yawAngle(-90.0f)
, _pitchAngle(0.0f)
,_firstPressMouse(false)
,_mouseDown(false)
,_lastXpos(0.0f)
,_lastYpos(0.0f)
{
	
}

glm::mat4 Camera::getViewMatrix()
{
	return lookAt(_pos, _pos + _front, _up);
}

glm::vec3 Camera::getPos()
{
	return _pos;
}

glm::vec3 Camera::getFront()
{
	return _front;
}

GLfloat Camera::getAscept()
{
	return _ascept;
}

GLfloat Camera::setCameraSensitivity(GLfloat sensitivity)
{
	return _sensitivity = sensitivity;
}

void Camera::processKeyboard(Direction direction, GLfloat deltaTime)
{
	switch (direction)
	{
	case Direction::FOWARD:
		_pos += _front * deltaTime;
		break;
	case Direction::BACKARD:
		_pos -= _front * deltaTime;
		break;
	case Direction::LEFT:
		_pos -= normalize(cross(_front, _up)) * deltaTime;
		break;
	case Direction::RIGHT:
		_pos += normalize(cross(_front, _up)) * deltaTime;
		break;
	}
}

void Camera::processMouseButton(MouseAction action)
{
	if (action == MouseAction::PRESS)
	{
		_firstPressMouse = true;
		_mouseDown = true;
	}
	else if (action == MouseAction::RELEASE)
	{
		_mouseDown = false;
	}
}

void Camera::processMouseCursor(GLfloat xpos, GLfloat ypos)
{
	if (!_mouseDown)return;

	if (_firstPressMouse)
	{
		_lastXpos = xpos;
		_lastYpos = ypos;
		_firstPressMouse = false;
	}

	GLfloat xoffset = xpos - _lastXpos;
	GLfloat yoffset = _lastYpos - ypos;
	_lastXpos = xpos;
	_lastYpos = ypos;

	xoffset *= _sensitivity;
	yoffset *= _sensitivity;

	_yawAngle += xoffset;
	_pitchAngle += yoffset;

	if (_pitchAngle > 89.0f)
		_pitchAngle = 89.0f;
	if (_pitchAngle < -89.0f)
		_pitchAngle = -89.0f;

	vec3 front;
	front.x = cos(radians(_yawAngle)) * cos(radians(_pitchAngle));
	front.y = sin(radians(_pitchAngle));
	front.z = sin(radians(_yawAngle)) * cos(radians(_pitchAngle));
	_front = normalize(front);
}

void Camera::processMouseScroll(GLfloat offset)
{
	if (_ascept >= 1.0f && _ascept <= 45.0f)
	{
		_ascept -= offset;
		if (_ascept <= 1.0f)
			_ascept = 1.0f;
		if (_ascept >= 45.0f)
			_ascept = 45.0f;
	}
}
