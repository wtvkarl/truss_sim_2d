#include "Point.h"
#include <format> 

Point::Point()
{}

Point::Point(GLfloat x, GLfloat y)
{
	xpos = x;
	ypos = y;
	zpos = 0;
	force = Force(0, 0); //default force is no net force

	//default color is white
	//rgba floats go from 0.0 to 1.0, not 0 to 255!
	r_val = 0.35f;
	g_val = 0.57f;
	b_val = 0.72f;
}

Point::Point(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b)
{
	xpos = x;
	ypos = y;
	zpos = 0;
	r_val = r;
	g_val = g;
	b_val = b;
}

void Point::printPoint()
{
	printf("pID [%.2f, %.2f]\tForce: <%.2f, %.2f> @ %.2f degs\n", xpos, ypos, force.fx, force.fy, force.angle);
}

void Point::addForce(Force f)
{
	force = f;
}

std::string Point::get_norm_coords()
{
	return std::to_string(norm_x(xpos)) + ", " +
		std::to_string(norm_y(ypos)) + ", 0";

	std::cout << norm_y(ypos) << "\t" << norm_x(xpos) << "\n";
}