#include "Simulator.h"

Simulator::Simulator()
{
}

void Simulator::printAllPoints()
{
	for (int i = 0; i < points.size(); i++) {
		points.at(i).printPoint();
	}
}