#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
:_program(0)
{
	if (vertexPath == nullptr || fragmentPath == nullptr) return;
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	vShaderFile.exceptions(ifstream::badbit);
	fShaderFile.exceptions(ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (const ifstream::failure& e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	linkProgram(vertexCode.c_str(), fragmentCode.c_str());
}

GLuint Shader::loadShader(GLint shaderType, const GLchar* sharderSource)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &sharderSource, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512] = "";
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR SHADER:" << infoLog << endl;
	}
	else
	{
		return shader;
	}

	return 0;
}


void Shader::linkProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
{
	GLuint shaderProgram = glCreateProgram();
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	if (vertexShader != 0 && fragmentShader != 0)
	{
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		GLint success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			cout << "ERROR PROGRAM:" << infoLog << endl;
			return;
		}
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	_program = shaderProgram;
}

void Shader::use()
{
	if (_program != 0)
	{
		glUseProgram(_program);
	}
}

GLint Shader::getProgram() const
{
	return _program;
}
