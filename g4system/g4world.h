#ifndef  G4WORLD_H
#define  G4WORLD_H 1

// gsystem
#include "gworld.h"

// g4system
#include "g4volume.h"


// a world is a collection of GSystem, their
class G4World
{
public:
	// constructor from a GWorld, using verbosity
	G4World(GWorld *gworld, GOptions* opt);

	~G4World() {
		// now deleting events
//		for (auto& [keys, values]: (*g4volumesMap) ) {
//			delete values;
//		}
//
//		delete g4volumesMap;
	}

private:
	// the key has the form gsystem/gvolumename
	map<string, G4Volume*> *g4volumesMap;

	string g4FactoryNameFromSystemFactory(string factory);

public:
	G4Volume* getG4Volume(string volumeName) {

		if ( g4volumesMap->find(volumeName) != g4volumesMap->end() ) {
			return (*g4volumesMap)[volumeName];
		}
		return nullptr;
	}


};


#endif

