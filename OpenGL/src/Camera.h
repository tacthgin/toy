#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	enum class Direction
	{
		FOWARD,
		BACKARD,
		LEFT,
		RIGHT
	};

	enum class MouseAction
	{
		PRESS,
		RELEASE
	};

	Camera(const glm::vec3& pos);
	glm::mat4 getViewMatrix();
	glm::vec3 getPos();
	glm::vec3 getFront();
	GLfloat getAscept();
	GLfloat setCameraSensitivity(GLfloat sensitivity);
	void processKeyboard(Direction direction, GLfloat deltaTime);
	void processMouseButton(MouseAction action);
	void processMouseCursor(GLfloat xpos, GLfloat ypos);
	void processMouseScroll(GLfloat offset);
private:
	glm::vec3 _pos;
	glm::vec3 _front;
	glm::vec3 _up;
	GLfloat _ascept;
	GLfloat _sensitivity;
	GLfloat _yawAngle;
	GLfloat _pitchAngle;
	GLboolean _firstPressMouse;
	GLboolean _mouseDown;
	GLfloat _lastXpos;
	GLfloat _lastYpos;
};

#endif
