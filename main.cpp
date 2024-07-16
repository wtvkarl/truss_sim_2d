#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <stb/stb_image.h>

#include "Rectangle.h"
#include "VertexHandler.h"

const int WIDTH = 1000;
const int HEIGHT = 800;

enum Mode { NORMAL, PLACE, CONNECT };
Mode STATE_MODE = NORMAL;

GLfloat cursorX = 0, cursorY = 0; //cursor pos
GLfloat hLockCursorX = 0, vLockCursorY = 0; //cursor constrained positions
GLfloat x_norm = 0, y_norm = 0; //normalized cursor 

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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

	//we could probably put this in a seperate class.. (TODO)
	int width, height, channels;
	unsigned char* pixels = stbi_load("images/place_cursor.png", &width, &height, &channels, 4);

	if (pixels == NULL)
	{
		std::cout << "failed to load image" << "\n";
		glfwTerminate();
	}

	GLFWimage image;
	image.width = width;
	image.height = height;
	image.pixels = pixels;

	GLFWcursor* placeCursor = glfwCreateCursor(&image, 0, 0);

	while (!glfwWindowShouldClose(window)) // main loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glDrawElements(GL_TRIANGLES, vHandler.indices.size(), GL_UNSIGNED_INT, 0);
		
		//clean this up and maybe put it in its own function...

		//we can merge this block of code with the one in the main loop 
		//put into function (TO-DO)

		VAO1.Bind();

		//this code works, DO NOT TOUCH THIS BLOCK.
		VBO1.updateVertexData(vHandler.vertices);
		EBO1.updateIndexData(vHandler.indices);
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		if (STATE_MODE == PLACE)
		{
			glfwSetCursor(window, placeCursor);
			
		}
		else {
			glfwSetCursor(window, NULL);
		}
		
		vHandler.checkPositionConstraints(window);

		glfwSwapBuffers(window); // double buffers
		glfwPollEvents(); //keep this for basic responsiveness
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
			if (vHandler.rectangles.empty())
			{
				vHandler.addRectangle(cursorX, cursorY, rectSize, rectSize);
				hLockCursorX = cursorX;
				vLockCursorY = cursorY;
				return;
			}

			GLfloat r_x, r_y;

			r_x = vHandler.constrainedH ? hLockCursorX : cursorX;
			r_y = vHandler.constrainedV ? vLockCursorY : cursorY;

			vHandler.addRectangle(r_x, r_y, rectSize, rectSize);
		}
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_Q)
		{
			STATE_MODE = NORMAL;
			std::cout << "Selected Mode: NORMAL" << "\n";
		}
		else if (key == GLFW_KEY_W)
		{
			STATE_MODE = PLACE;
			std::cout << "Selected Mode: PLACE" << "\n";
		}
		else if (key == GLFW_KEY_E)
		{
			STATE_MODE = CONNECT;
			std::cout << "Selected Mode: CONNECT" << "\n";
		}

		else if (key == GLFW_KEY_SPACE)
		{
			//printf("[%.2f, %.2f] -> [%.2f, %.2f]\n", cursorX, cursorY, x_norm, y_norm;
		}
		
		else if (key == GLFW_KEY_LEFT_SHIFT)
		{
			if (vHandler.rectangles.empty())
				return;

			hLockCursorX = vHandler.rectangles.back().xPos;
		}

		else if (key == GLFW_KEY_LEFT_CONTROL)
		{
			if (vHandler.rectangles.empty())
				return;

			vLockCursorY = vHandler.rectangles.back().yPos;
		}
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