#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <stb/stb_image.h>
#include "StateManager.h"

#include "Rectangle.h"
#include "VertexHandler.h"

const int WIDTH = 1000;
const int HEIGHT = 800;

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

VertexHandler vHandler;

int main()
{
	glfwInit(); //tells opengl to start up

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //only use core profile

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Truss Simulator", NULL, NULL); //create window statement

	if (window == NULL) //if the window fails to create, end the program
	{
		std::cout << "failed to create window :(" << '\n';
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window); //specify which window is being used

	gladLoadGL(); //load glad API

	glViewport(0, 0, WIDTH, HEIGHT); // specify bounds of window

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vHandler.vertices);
	EBO EBO1(vHandler.indices);
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetKeyCallback(window, key_callback);


	while (!glfwWindowShouldClose(window)) // main loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glDrawElements(GL_TRIANGLES, vHandler.indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // double buffers
		glfwPollEvents(); //keep this for basic responsiveness

		//clean this up and maybe put it in its own function...

		//we can merge this block of code with the one in the main loop 
		//put into function (TO-DO)

		VAO1.Bind();

		//this code works, DO NOT TOUCH THIS BLOCK.
		VBO1.updateVertexData(vHandler.vertices);
		EBO1.updateIndexData(vHandler.indices);
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// ----- input functions -----

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS && STATE_MODE == PLACE)
		{
			//subtracting half the rect size to center on cursor
			Rectangle r(cursorX - 10, cursorY - 10, rectSize, rectSize);
			vHandler.addRectangle(r);
		}
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		STATE_MODE = NORMAL;
		std::cout << "Selected Mode: NORMAL" << "\n";
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		STATE_MODE = PLACE;
		std::cout << "Selected Mode: PLACE" << "\n";
	}
	else if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		STATE_MODE = CONNECT;
		std::cout << "Selected Mode: CONNECT" << "\n";
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		printf("[%.2f, %.2f] -> [%.2f, %.2f]\n", cursorX, cursorY, x_norm, y_norm);
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	cursorX = (GLfloat)xpos;
	cursorY = (GLfloat)ypos;

	//centered based off window dimensions
	// width = 1000, height = 800;
	x_norm = (GLfloat)(xpos - 500) / 500;
	y_norm = (GLfloat)(ypos - 400) / -400;
}