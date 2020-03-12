#ifndef SECONDFACTORY_H
#define SECONDFACTORY_H 1

#include "Car.h"

class Dodge : public Car
{
public:
	Dodge();
	void go();
	double dodgeVar[2][2];
};

extern "C" Car* CarFactory(void) {
	return static_cast<Car*>(new Dodge);
}


#endif // SECONDFACTORY_H
