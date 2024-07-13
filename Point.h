#ifndef POINT_CLASS_H
#define POINT_CLASS_H

#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <iostream>
#include "Force.h"

class Point
{
	public:
		GLfloat xpos, ypos, zpos;
		GLfloat r_val, g_val, b_val;
		Force force;

		//this is 2d so zpos is always 0
		Point();
		Point(GLfloat x, GLfloat y);
		Point(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);

		void printPoint();
		void addForce(Force f);
		std::string get_norm_coords();
};


//based off of the length and height of the window (1000, 800, respectively
//didn't feel like making variables for it just easier to hardcode it, not sure if it's bad practice...

static GLfloat norm_x(GLfloat x)
{
	return (x - 500.0f) / 500.0f;
}

static GLfloat norm_y(GLfloat y)
{
	return (y - 400.0f) / -400.0f;
}

#endif