#ifndef  G4VOLUMES_H
#define  G4VOLUMES_H 1

// geant4
#include "G4PVPlacement.hh"

// gvolume
#include "g4volume.h"

// glibrary
#include "gsystem.h"

class G4Volumes
{

public:
	G4Volumes(GSystem* gsystem, int verbosity) {
		g4volumes = new map<string, G4Volume*>;
		buildGSystem(gsystem, verbosity);
	}

	G4VSolid*          getSolid(string vname) const;
	G4LogicalVolume*   getLogical(string vname) const;
	G4VPhysicalVolume* getPhysical(string vname) const;

	~G4Volumes() {
		delete g4volumes;
	}

private:

	// the key has the form system/volumename
	map<string, G4Volume*> *g4volumes;

private:

	void buildGSystem(GSystem* gsystem, int verbosity);
	void buildWorld(int verbosity);
	G4Volume* getG4Volume(string name) const;

	void registerFactoriesAndBuildG4Volumes(GSystem* gsetup, GOptions* gopt);

public:
	void addG4Volume(G4Volume *g4v, string name);

};

#endif


