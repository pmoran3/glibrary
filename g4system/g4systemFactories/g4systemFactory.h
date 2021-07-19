#ifndef G4SYSTEMFACTORY_H
#define G4SYSTEMFACTORY_H 1


// g4system
#include "gworld.h"


// G4SetupFactory factory
class G4SystemFactory
{
public:
	// returns true if the system could be built
	// returns false if dependencies are not met
	virtual bool loadG4System(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s) = 0;

	virtual ~G4SystemFactory() = default;

private:
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
};


#endif
