/// \file example.cc

// example on how to use the gdynamic library

// gdynamic
#include "gdynamic.h"

// gfactory
#include "gfactory.h"

// c++
#include <iostream>
using namespace std;


//! example of main declaring GOptions
int main(int argc, char* argv[])
{

	GManager manager(1);

	// DL is the name of the
	manager.registerDL("ctofRoutinesExample");

	map<string, GDynamic*> dynamicRoutines;
	dynamicRoutines["ctof"] = manager.LoadObjectFromLibrary<GDynamic>("ctofRoutinesExample");


	shared_ptr<GDynamic> globalCtof1(manager.LoadObjectFromLibrary<GDynamic>("ctofRoutinesExample"));
	shared_ptr<GDynamic> globalCtof2(manager.LoadObjectFromLibrary<GDynamic>("ctofRoutinesExample"));

	// increments reference count
	// to be used in the local thread
	auto globalCtof3(globalCtof2);

	cout << dynamicRoutines["ctof"] << " " << globalCtof1 << " " << globalCtof2 << " " << globalCtof3 << endl;


	dynamicRoutines["ctof"]->loadConstants(1, "original");
	globalCtof1->loadConstants(1, "original");
	globalCtof2->loadConstants(1, "original");
	globalCtof3->loadConstants(1, "original");


	return 1;
}

