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
		std::vector<GLuint> indices = {
			2,3,1,
			0,1,2,
			4,5,6,
			6,7,5
		};

		const char* vertexDataFile = "util/vertexdata.txt";
		int numVerts = 0;

		void addRectangle(Rectangle rect);
		//this is variable in size and updates every time rectangles are added
		void printVertDrawVec();
		

	private:
		void writeVertexData(const char* filename, Point pts[4]);

		void insert_vert_to_drawvec(GLfloat x, GLfloat y, GLfloat z);
};

#endif