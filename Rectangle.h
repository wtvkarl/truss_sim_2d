#ifndef RECTANGLE_CLASS_H
#define RECTANGLE_CLASS_H

#include <GLFW/glfw3.h>
#include <vector>
#include "Point.h"

const GLfloat rectSize = 20;

class Rectangle
{
public:
	std::vector<GLfloat> vertices;
	Point points[4];
	GLfloat xPos, yPos;
	GLfloat length, height;

	Rectangle();
	Rectangle(GLfloat xpos, GLfloat ypos, GLfloat len, GLfloat h);

	Point get_pos();

private:
	void init_norm_coords();

};

#endif