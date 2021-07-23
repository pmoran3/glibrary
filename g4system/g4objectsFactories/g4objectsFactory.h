#ifndef G4SYSTEMFACTORY_H
#define G4SYSTEMFACTORY_H 1


// glibrary
#include "goptions.h"

// gsystem
#include "gvolume.h"

// g4system
#include "g4volume.h"

// geant4
#include "G4VSolid.hh"

// c++
#include <map>
using std::map;

// G4SetupFactory factory
class G4ObjectsFactory
{
public:
	// returns true if the system could be built
	// returns false if dependencies are not met
	virtual bool loadG4System(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4smap) = 0;

	virtual ~G4ObjectsFactory() = default;

protected:
	// geant4 objects getters
	G4VSolid*          getSolidFromMap(   string vname, map<string, G4Volume*> *g4s) const;
	G4LogicalVolume*   getLogicalFromMap( string vname, map<string, G4Volume*> *g4s) const;
	G4VPhysicalVolume* getPhysicalFromMap(string vname, map<string, G4Volume*> *g4s) const;

	// geant4 dependencies checkers
	bool checkSolidDependencies(   bool verbosity, GVolume *s, map<string, G4Volume*> *g4s);
	bool checkLogicalDependencies( bool verbosity, GVolume *s, map<string, G4Volume*> *g4s);
	bool checkPhysicalDependencies(bool verbosity, GVolume *s, map<string, G4Volume*> *g4s);

	G4RotationMatrix *getRotation(GVolume *s);
	G4ThreeVector     getPosition(GVolume *s);

	bool getVerbosity(GOptions* gopt, string vname) {

		int    verbosity = gopt->getInt("g4systemv");
		string logVolume = gopt->getString("logVolume");

		return (verbosity == GVERBOSITY_DETAILS) || (vname == logVolume);
	}

};


#endif
