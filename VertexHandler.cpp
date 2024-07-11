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
	updateIndexVec();

	//#rects * 4 points per rect * 3 coords per point (x,y,z)
	numElements = rectangles.size() * 4 * 3;

	for (Point p : rect.points)
	{
		GLfloat x = p.xpos;
		GLfloat y = p.ypos;
		GLfloat z = p.zpos;

		addVertexToVec(x, y, z);
	}

	writeVertexData(vertexDataFile, rect.points);
		
}

void VertexHandler::addRectangle(GLfloat x, GLfloat y, GLfloat length, GLfloat height)
{
	Rectangle r(x, y, length, height);
	addRectangle(r);
}

void VertexHandler::printVertVec()
{
	for (GLfloat f : vertices)
	{
		std::cout << f << "\n";
	}
}

void VertexHandler::printIndexVec()
{
	int elemCount = 0;
	for (GLuint u : indices)
	{
		elemCount++;
		if (elemCount == 3)
		{
			elemCount = 0;
			std::cout << u << "\n";
		}
		else
			std::cout << u << ",";
	}
}


// ----- private methods -----

void VertexHandler::addVertexToVec(GLfloat x, GLfloat y, GLfloat z)
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

/* everytime a rectangle is added to the vertex vector,
*  a total of 4 vertices are added, which can be split into 
*  2 triangles, which require 6 indices. 
* 
*  the way rectangles are "built" in this program is 
*  points are added one by one clockwise starting from the top left.
*
*  index pattern follows as such:
*  0,1,2 (1st triangle)
*  2,3,1 (2nd triangle)
* 
*  we just have to shift the starting index everytime indices is updated.
*/

void VertexHandler::updateIndexVec()
{
	//starting index is 0 for the first rectangle
	int startingIndex = (rectangles.size() - 1) * 4;
	
	//right triangle
	indices.push_back(startingIndex);
	indices.push_back(startingIndex + 1);
	indices.push_back(startingIndex + 2);

	//left triangle
	indices.push_back(startingIndex + 2);
	indices.push_back(startingIndex + 3);
	indices.push_back(startingIndex + 1);
}
