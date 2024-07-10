#include "VertexHandler.h"
#include <algorithm>
#include <iostream>
#include <fstream>

VertexHandler::VertexHandler()
{
	//this clears the vertex data file everytime the app is opened
	std::ofstream file;
	file.open(vertexDataFile, std::ofstream::out | std::ofstream::trunc);
	file.close();
}

// ----- public methods ------

void VertexHandler::addRectangle(Rectangle rect)
{
	rectangles.push_back(rect);
	numVerts = rectangles.size() * 4 * 3;

	for (Point p : rect.points)
	{
		GLfloat x = p.xpos;
		GLfloat y = p.ypos;
		GLfloat z = p.zpos;

		insert_vert_to_drawvec(x, y, z);
	}

	writeVertexData(vertexDataFile, rect.points);

	std::cout << numVerts << "\n";
		
}

void VertexHandler::printVertDrawVec()
{
	for (GLfloat f : vertices)
	{
		std::cout << f << "\n";
	}
}

//TO DO: convert string of numbers into array of GLfloat


// ----- private methods -----

void VertexHandler::insert_vert_to_drawvec(GLfloat x, GLfloat y, GLfloat z)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void VertexHandler::writeVertexData(const char* filename, Point pts[4])
{
	std::fstream file;
	file.open(vertexDataFile, std::ios::app);

	if (!file)
		std::cout << "file not found.";
	else {
		for (int i = 0; i < 4; i++)
		{
			file << pts[i].xpos << ", "
				<< pts[i].ypos << ", "
				<< pts[i].zpos << " \n";
		}
	}

	file.close();
}
