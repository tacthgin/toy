#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

using namespace std;

const GLchar* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 color;\n"
	"out vec3 outColor;\n"
	"void main()\n"
	"{\n"
		"gl_Position = vec4(position, 1.0);\n"
		"outColor = color;\n"
	"}\0";

const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"in vec3 outColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
		"color = vec4(outColor, 1.0f);\n"
	"}\n";

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);//关闭glfw
	}
}

int main()
{
	//初始化glfw窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //core_profile 核心模式
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //无法调整窗口大小

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback); //设置按键回调

	glewExperimental = GL_TRUE; //使glew更多使用现代化技术，防止在核心模式出现问题
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW err:" << glewGetErrorString(err) << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height); //设置opengl窗口大小

	GLuint shaderProgram = linkProgram();
	
	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	/*
	GLfloat vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,  
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f 
	};

	GLuint indics[] = {
		0, 1, 2,
		0, 2, 3
	};*/

	GLuint VBO, VAO, IBO;
	glGenVertexArrays(1, &VAO); //创建vao
	glGenBuffers(1, &VBO); //创建vbo
	glGenBuffers(1, &IBO); //创建ibo

	glBindVertexArray(VAO); //绑定vao

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓冲对象
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //复制顶点数据到缓冲对象
	/*
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); //绑定索引缓冲
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indics), indics, GL_STATIC_DRAW); */

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); //设置顶点属性
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //设置顶点属性
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //解绑vao

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//处理触发事件(键盘,鼠标)

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		/*
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint colorLocation = glGetUniformLocation(shaderProgram, "outColor");
		glUniform4f(colorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	
	glfwTerminate();
	return 0;
}



