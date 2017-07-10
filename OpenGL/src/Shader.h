#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//ʹ����ɫ���������
	void use();
	GLint getProgram() const;
private:
	GLuint loadShader(GLint shaderType, const GLchar* sharderSource);
	void linkProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
private:
	//����id
	GLint _program;
};

#endif // !_SHADER_H_
