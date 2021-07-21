#ifndef G4CADSYSTEMFACTORY_H
#define G4CADSYSTEMFACTORY_H 1

// g4system
#include "g4systemConventions.h"
#include "g4systemFactories/g4systemFactory.h"

// system factory
class G4CadSystemFactory : G4SystemFactory
{
public:

	G4CadSystemFactory() = default;


	bool loadG4System(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s) {

		int verbosity = gopt->getInt("g4systemv");

		if(verbosity >= GVERBOSITY_SUMMARY) {
			G4cout << G4SYSTEMLOGHEADER << " Importing cad volumes." << G4endl;
		}

//		bool sbuild = buildSolid(gopt, s, g4s);
//		bool lbuild = buildLogical(gopt, s, g4s);
//		bool pbuild = buildPhysical(gopt, s, g4s);
//
//		if(verbosity >= GVERBOSITY_DETAILS) {
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
//	bool buildSolid(   GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);
//	bool buildLogical( GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);
//	bool buildPhysical(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s);

};


#endif

