#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

using namespace std;

const char* vertexShaderSource = {
	"#version 330 core"
	"layout (location = 0) in vec3 position;"
	"void main()"
	"{"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);"
	"}"
};

const char* fragmentShaderSource = {
	"#version 330 core"
	"out vec4 color;"
	"void main()"
	"{"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
	"}"
};

GLuint loadShader(GLint shaderType, const char* sharderSource)
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

GLuint linkProgram()
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
		}
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "noob", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	    return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwTerminate();
	return 0;
}



