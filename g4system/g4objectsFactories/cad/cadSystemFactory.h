#ifndef G4CADSYSTEMFACTORY_H
#define G4CADSYSTEMFACTORY_H 1

// g4system
#include "g4systemConventions.h"
#include "g4objectsFactories/g4objectsFactory.h"

// Cadmesh single header library, @tag 2.0.3
// https://github.com/christopherpoole/CADMesh
#include "CADMesh.hh"


// system factory
class G4CadSystemFactory : G4ObjectsFactory
{
public:
	bool loadG4System(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s) {

		int verbosity = gopt->getInt(G4SYSTEMVERBOSITY);
		string vname = s->getMapName();

		if(verbosity >= GVERBOSITY_SUMMARY) {
			G4cout << G4SYSTEMLOGHEADER << "Importing cad volumes <" << vname << ">" << G4endl;
		}

		//G4VSolid*          sbuild = buildSolid(gopt, s, g4s);
//		bool lbuild = buildLogical(gopt, s, g4s);
//		bool pbuild = buildPhysical(gopt, s, g4s);
//
//		if(verbosity == GVERBOSITY_DETAILS) {
//			string vname = s->getName();
//			string solid = sbuild ? " solid build, "    : " solid not build, ";
//			string logic = lbuild ? " logical build, "  : " logical not not build, ";
//			string physi = pbuild ? " physical build. " : " physical not build. ";
//			G4cout << G4SYSTEMLOGHEADER << " g4volume <" << vname << "> solid, logical and physical volume pointers: " << solid << logic << physi << G4endl;
//		}
//
//		if(sbuild && lbuild && pbuild) {
//			return true;
//		} else {
//			return false;
//		}
		return true;
	}

private:
	G4VSolid*          buildSolid(   GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);
//	G4LogicalVolume*   buildLogical( GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);
//	G4VPhysicalVolume* buildPhysical(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);

};


#endif

