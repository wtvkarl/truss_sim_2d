#ifndef VERTEX_HANDLER_IMPLEMENTATION_H
#define VERTEX_HANDLER_IMPLEMENTATION_H

#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include "Point.h"

void writeToVertexFile(const char* filename, Point p)
{
	std::ofstream file(filename);

	file << p.get_norm_coords() << "\n";

	file.close();
}


#endif