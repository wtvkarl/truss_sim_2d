#ifndef FORCE_CLASS_H
#define FORCE_CLASS_H

#include <cmath>
#include <iostream>

constexpr auto PI = 3.14159; //defines this variable for all cpp files that use this h file

class Force
{
	public:
		double fx;
		double fy;
		double angle; 

		Force();
		Force(double fx, double fy);

		void printForce();

};

#endif // !FORCE_CLASS_H
