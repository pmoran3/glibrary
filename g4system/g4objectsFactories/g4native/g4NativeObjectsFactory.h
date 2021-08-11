#ifndef G4NATIVESYSTEMFACTORY_H
#define G4NATIVESYSTEMFACTORY_H 1

// g4system
#include "g4systemConventions.h"
#include "g4objectsFactories/g4objectsFactory.h"

// system factory
class G4NativeSystemFactory : G4ObjectsFactory
{
public:
	bool loadG4System(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s) {


		int verbosity = gopt->getInt(G4SYSTEMVERBOSITY);
		string vname = s->getMapName();

		if(verbosity >= GVERBOSITY_SUMMARY) {
			G4cout << G4SYSTEMLOGHEADER << "Building geant4 volume originating from <" << vname << ">" << G4endl;
		}

		G4VSolid*          sbuild = buildSolid(gopt, s, g4s);
		G4LogicalVolume*   lbuild = buildLogical(gopt, s, g4s);
		lbuild->SetVisAttributes(createVisualAttributes(s));
		G4VPhysicalVolume* pbuild = buildPhysical(gopt, s, g4s);

		if(verbosity >= GVERBOSITY_DETAILS) {
			string solid = sbuild != nullptr ? " solid build, "    : " solid not build, ";
			string logic = lbuild != nullptr ? " logical build, "  : " logical not not build, ";
			string physi = pbuild != nullptr ? " physical build. " : " physical not build. ";
			G4cout << G4SYSTEMLOGHEADER << "g4volume <" << vname << "> " << solid << logic << physi << " with pointers: " << sbuild << ", " << lbuild << ", " << pbuild << G4endl;
		}

		if(sbuild && lbuild && pbuild) {
			return true;
		} else {
			return false;
		}
	}

private:
	G4VSolid*          buildSolid(   GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);
	G4LogicalVolume*   buildLogical( GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);
	G4VPhysicalVolume* buildPhysical(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);

	// solid
	vector<string> descriptionsOfParameters(GVolume *s); // returns description of geant4 constructor parameters
	vector<double> checkAndReturnParameters(GVolume *s); // checks and returns the number of parameters matches the geant4 constructor
};


#endif

