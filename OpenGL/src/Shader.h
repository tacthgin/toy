#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
private:
	GLint _program;
};

#endif // !_SHADER_H_

