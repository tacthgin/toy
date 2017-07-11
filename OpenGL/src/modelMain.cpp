#include <iostream>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <SOIL/SOIL.h>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

using namespace std;
using namespace glm;

const int screenWidth = 800;
const int screenHeight = 600;

bool keys[1024];

Camera camera(vec3(0.0f, 0.0f, 3.0f));

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			camera.processMouseButton(Camera::MouseAction::PRESS);
		}
		else if (action == GLFW_RELEASE)
		{
			camera.processMouseButton(Camera::MouseAction::RELEASE);
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.processMouseCursor(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
}

void do_movement(GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		camera.processKeyboard(Camera::Direction::FOWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S])
	{
		camera.processKeyboard(Camera::Direction::BACKARD, deltaTime);
	}

	if (keys[GLFW_KEY_A])
	{
		camera.processKeyboard(Camera::Direction::LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D])
	{
		camera.processKeyboard(Camera::Direction::RIGHT, deltaTime);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW err:" << glewGetErrorString(err) << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	Shader modelShader("../shaders/model.vs", "../shaders/model.frag");
	Model loadedModel("../images/nanosuit/nanosuit.obj");

	GLfloat lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		do_movement(deltaTime);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelShader.use();

		GLuint modelLoc = glGetUniformLocation(modelShader.getProgram(), "model");
		GLuint viewLoc = glGetUniformLocation(modelShader.getProgram(), "view");
		GLuint projectionLoc = glGetUniformLocation(modelShader.getProgram(), "projection");

		mat4 model;
		model = translate(model, vec3(0.0f, -1.75f, 0.0f));
		model = scale(model, vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

		mat4 view = camera.getViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

		mat4 projection;
		projection = perspective(camera.getAscept(), (float)screenWidth / screenHeight, 0.1f, 100.0f);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

		loadedModel.draw(modelShader);

		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}



