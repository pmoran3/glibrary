#include "gfactory.h"
#include "ShapeFactory.h"
#include "Car.h"

#include <iostream>
using namespace std;

// managerA: loads known classes Triangle and Box from the base Shape, in ShapeFactory.h
// managerB: loads DLL that instantiate derived factories - we only know of the base class, in this case "Car"

int main()
{
	GManager managerA;    // no verbosity

	// A manages Shapes
	// registering 3 shape classes
	// notice, here we know of them through the header
	managerA.RegisterObjectFactory<Triangle>("triangle");
	managerA.RegisterObjectFactory<Box>("box1");
	managerA.RegisterObjectFactory<Box>("box2");

	// putting A factory in map
	map<string, Shape*> fff;
	fff["triangle"] = managerA.CreateObject<Shape>("triangle");
	fff["box1"]     = managerA.CreateObject<Shape>("box1");
	fff["box2"]     = managerA.CreateObject<Shape>("box2");

	// aShape is same pointer as map element
	Shape* aShape = fff["triangle"];

	// calling base and derived methods
	aShape->Area();
	fff["triangle"]->Area();
	fff["box1"]->Area();

	managerA.clearDLMap();

	// B manages Cars. Notice, we do not need the derived class headers here!
	// PRAGMA: These two names must match in the registerDL and in the LoadObjectFromLibrary:
	// tesla
	// that's ok but need to spit error if that doesn't happen
	GManager managerB(1); // no verbosity of 1
	managerB.registerDL("teslaFactory");
	managerB.registerDL("fordFactory");
	
	map<string, Car*> ggg;
	ggg["tesla"] = managerB.LoadObjectFromLibrary<Car>("teslaFactory");
	ggg["ford"]  = managerB.LoadObjectFromLibrary<Car>("fordFactory");
	Car* aCar = ggg["ford"];


	// calling base and derived method
	ggg["tesla"]->go();
	ggg["ford"]->go();

	cout << " Shape pointers: " << fff["triangle"] << " " << aShape << endl;
	cout << " Car pointers: " << ggg["ford"] << " " << aCar << endl;


	// why this need to be cleared here, and not after the factories are
	// put in the map?
	managerB.clearDLMap();

}



