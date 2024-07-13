#include "Rectangle.h"

Rectangle::Rectangle(GLfloat xpos, GLfloat ypos, GLfloat len, GLfloat h)
{
	x = xpos;
	y = ypos;
	length = len;
	height = h;
	init_norm_coords();

}

Point Rectangle::get_pos()
{
	return Point(x, y);
}

//normalizing functions found in Point.h 
void Rectangle::init_norm_coords()
{
	Point topLeft(norm_x(x), norm_y(y));
	Point topRight(norm_x(x + length), norm_y(y));
	Point bottomLeft(norm_x(x), norm_y(y + height));
	Point bottomRight(norm_x(x + length), norm_y(y + height));

	//go in clockwise order starting from topLeft (remember this for indexing)
	//don't forget the arrows when assigning a value to a specific object's array
	this->points[0] = topLeft;
	this->points[1] = topRight;
	this->points[2] = bottomLeft;
	this->points[3] = bottomRight;
}