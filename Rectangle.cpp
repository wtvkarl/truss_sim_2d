#include "Rectangle.h"
#include "VertexHandler.h"

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

void Rectangle::init_norm_coords()
{
	Point topLeft(norm_x(x), norm_y(y));
	Point topRight(norm_x(x + length), norm_y(y));
	Point bottomLeft(norm_x(x), norm_y(y + height));
	Point bottomRight(norm_x(x + length), norm_y(y + height));

	topLeft.printPoint();
	topRight.printPoint();
	bottomLeft.printPoint();
	bottomRight.printPoint();

	//clockwise order
	points[0] = topLeft;
	points[1] = topRight;
	points[2] = bottomRight; 
	points[3] = bottomLeft;

	

}
