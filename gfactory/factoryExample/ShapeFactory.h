#ifndef FIRSTFACTORY_H
#define FIRSTFACTORY_H 1

#include <string>
using namespace std;

class Shape
{
public:
	virtual void Area() = 0;
	virtual ~Shape() = default;

};


class Triangle : Shape
{

public:
	void Area();
};


class Box : Shape
{

public:
	void Area();
};


#endif // FIRSTFACTORY_H
