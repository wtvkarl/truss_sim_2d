#ifndef STATE_MANAGER_CLASS_H
#define STATE_MANAGER_CLASS_H

#include <GLFW/glfw3.h>
#include "Force.h"
#include "Point.h"

enum Mode {NORMAL, PLACE, CONNECT};
Mode STATE_MODE = NORMAL;

//dimensions of window
int WIDTH = 1000;
int HEIGHT = 800;

GLfloat curx = 0, cury = 0; //cursor pos
GLfloat x_norm = 0, y_norm = 0; //normalized cursor 

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	curx = (GLfloat) xpos;
	cury = (GLfloat) ypos;

	x_norm = (GLfloat)(xpos - 500) / 500;
	y_norm = (GLfloat)(ypos - 400) / -400;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
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
		printf("[%.2f, %.2f] -> [%.2f, %.2f]\n", curx, cury, x_norm, y_norm);
	}
}



#endif