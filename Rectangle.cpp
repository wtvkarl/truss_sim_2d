#include "Rectangle.h"

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(GLfloat xpos, GLfloat ypos, GLfloat len, GLfloat h)
{
	xPos = xpos;
	yPos = ypos;
	length = len;
	height = h;
	init_norm_coords();

}

Point Rectangle::get_pos()
{
	return Point(xPos, yPos);
}

//normalizing functions found in Point.h 
void Rectangle::init_norm_coords()
{
	Point topLeft(norm_x(xPos), norm_y(yPos));
	Point topRight(norm_x(xPos + length), norm_y(yPos));
	Point bottomLeft(norm_x(xPos), norm_y(yPos + height));
	Point bottomRight(norm_x(xPos + length), norm_y(yPos + height));

	//go in clockwise order starting from topLeft (remember this for indexing)
	//don't forget the arrows when assigning a value to a specific object's array
	this->points[0] = topLeft;
	this->points[1] = topRight;
	this->points[2] = bottomLeft;
	this->points[3] = bottomRight;
}