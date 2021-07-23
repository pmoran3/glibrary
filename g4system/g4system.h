#ifndef  G4VOLUMES_H
#define  G4VOLUMES_H 1

// geant4
#include "G4PVPlacement.hh"

// gvolume
#include "g4volume.h"

// glibrary
#include "gsystem.h"

// collection of geant4 volumes related to a gsystem
class G4System
{

public:
	// constructor, from command line or jcard
	G4System(string name, string f, int verbosity);

	~G4System() {
		delete g4volumesMap;
	}

private:


	// Factory that builds the detector
	string   factory;

public:
	map<string, G4Volume*>* getg4volumesMap() { return g4volumesMap;}

};

#endif


