#ifndef  G4WORLD_H
#define  G4WORLD_H 1

// gsystem
#include "gworld.h"

// g4system
#include "g4system.h"


// a world is a collection of GSystem, their
class G4World
{
public:
	// constructor from a GWorld, using verbosity
	G4World(GWorld *gworld, GOptions* opt);

private:
	map<string, G4System*> g4systemsMap;   // key is system name

	// the key has the form gsystem/gvolumename
	map<string, G4Volume*> *g4volumesMap;

	G4System* getOrCreateG4System(string sname, string factory, int verbosity);


};


#endif

