#include "Force.h"

Force::Force()
{}

Force::Force(double x, double y)
{
	fx = x;
	fy = y;
	angle = std::atan(y / x) * 180/PI; //PI is predefined in the header file
}

void Force::printForce()
{
	std::cout << "["
		<< fx << "," << fy << "] @ " 
		<< angle << "\n";
}