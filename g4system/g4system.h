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

//	G4VSolid*          getSolid(string vname) const;
//	G4LogicalVolume*   getLogical(string vname) const;
//	G4VPhysicalVolume* getPhysical(string vname) const;

	~G4System() {
		delete g4volumesMap;
	}

private:

	// the key has the form system/volumename
	map<string, G4Volume*> *g4volumesMap;

	// Factory that builds the detector
	string   factory;

private:

//	void buildG4System(GSystem* gsystem, int verbosity);
//	void addG4Volume(G4Volume *g4v, string name);
//	G4Volume* getG4Volume(string name) const;

public:
	map<string, G4Volume*>* getg4volumesMap() { return g4volumesMap ;}

};

#endif


