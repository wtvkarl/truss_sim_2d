#ifndef SIMULATOR_CLASS_H
#define SIMULATOR_CLASS_H

#include "Point.h"
#include <vector>

class Simulator
{
	public:
		std::vector<Point> points; //holds all points of the truss

		Simulator();

		void printAllPoints();
};

#endif // !SIMULATOR_CLASS_H
