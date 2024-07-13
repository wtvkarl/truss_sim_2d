#ifndef VERTEX_HANDLER_IMPLEMENTATION_H
#define VERTEX_HANDLER_IMPLEMENTATION_H

#include <GLFW/glfw3.h>

#include <iostream>
#include "Point.h"
#include "Rectangle.h"

class VertexHandler
{

public:
	VertexHandler();

	std::vector<Rectangle> rectangles;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	const char* vertexDataFile = "util/vertexdata.txt";

	void addRectangle(Rectangle rect);
	void addRectangle(GLfloat x, GLfloat y, GLfloat length, GLfloat height);

	//this is variable in size and updates every time rectangles are added
	void printVertVec();
	void printIndexVec();


private:
	void writeVertexData(const char* filename, Point pts[4]);
	void addPointToVector(Point p);
	void updateIndexVec();
};

#endif