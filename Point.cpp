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