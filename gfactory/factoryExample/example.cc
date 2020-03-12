#include "gfactory.h"
#include "ShapeFactory.h"
#include "Car.h"

#include <iostream>
using namespace std;

int main()
{
	GManager managerA;     // loads known classes Triangle and Box from the base Shape
	GManager managerB(1);  // loads DLL that instantiate derived factories - we only know of the base one in this case "Car"

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

	// B manages Cars. Notice, we do not need the derived class headers here!
	// PRAGMA: These two names must match in the registerDL and in the LoadObjectFromLibrary:
	// dodgeFactory
	// that's ok but need to spit error if that doesn't happen
	managerB.registerDL("dodgeFactory");
	managerB.registerDL("fordFactory");
	
	map<string, Car*> ggg;
	ggg["dodge"] = managerB.LoadObjectFromLibrary<Car>("dodgeFactory");
	ggg["ford"]  = managerB.LoadObjectFromLibrary<Car>("fordFactory");
	Car* aCar = ggg["ford"];

	for(int i=0; i<2; i++) {

		aShape->Area();
		fff["triangle"]->Area();
		fff["box1"]->Area();
	
		if(ggg["dodge"] != nullptr)
			ggg["dodge"]->go();
		if(ggg["ford"] != nullptr)
			ggg["ford"]->go();

		cout << " Shape pointers: " << fff["triangle"] << " " << aShape << endl;
		cout << " Car pointers: " << ggg["ford"] << " " << aCar << endl;

	}

	// why this need to be cleared here, and not after the factories are
	// put in the map?
	managerB.clearDLMap();

}



