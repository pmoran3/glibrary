// g4system
#include "g4NativeObjectsFactory.h"

// geant4
#include "G4NistManager.hh"
//#include "G4Material.hh"
//#include "G4LogicalVolume.hh"

// guts
#include "gutilities.h"

G4LogicalVolume* G4NativeSystemFactory::buildLogical(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s)
{
	string vname = s->getName();
	bool verbosity = getVerbosity(gopt, vname);

	// if it's a component, do nothing
	string matName = s->getMaterial();
	//if(matName == "component") return true;

	// dependencies are there, can build volume
	string dmat             = gopt->getString("defaultMaterial");
	bool useDefaultMaterial = gopt->getSwitch("useDefaultMaterial");

	// if the g4volume doesn't exist, create one and add it to the map
	G4Volume *thisG4Volume = nullptr;

	// check if g4s already exists
	// it could not exist if this is a copy
	if(g4s->find(vname) != g4s->end()) {
		thisG4Volume = (*g4s)[vname];
		// if the logical is already built, nothing to do
		// this can happen if it's a copy
		if(thisG4Volume->getLogical() != nullptr) return thisG4Volume->getLogical();

		// if the solid does not exist, can't build the logical
		if(thisG4Volume->getSolid() == nullptr) return nullptr;
	} else {
		thisG4Volume = new G4Volume();
	}

	G4NistManager* NISTman = G4NistManager::Instance();

	// looking for material
	G4Material* thisMaterial = NISTman->FindOrBuildMaterial(matName);
	// if not found, use the material specified in the options
	if(thisMaterial == nullptr && useDefaultMaterial) {
		G4cout << " ! Warning: material " << matName << " not found for volume " << vname << ". Using " << dmat << " instead." << G4endl;
		thisMaterial = NISTman->FindOrBuildMaterial(dmat);
		if(thisMaterial == nullptr) {
			// you set an option incorrectly, error!
			G4cerr << FATALERRORL << "options default material " << dmat << " not found. Exiting. Need to add (g)exit nice here." << G4endl;
			gexit(EC__G4MATERIALNOTFOUND);
		}
	}

	// everything is set to build the logical volumes.
	// The constructor (need link here) looks like:
	//	G4LogicalVolume(G4VSolid* pSolid,
	//					G4Material* pMaterial,
	//					const G4String& name,
	//					G4FieldManager* pFieldMgr=0,
	//					G4VSensitiveDetector* pSDetector=0,
	//					G4UserLimits* pULimits=0,
	//					G4bool optimise=true);
	// Constructor. The solid and material pointer must be non null.
	// The parameters for field, detector and user limits are optional.
	// The volume also enters itself into the logical volume Store.
	// Optimisation of the geometry (voxelisation) for the volume
	// hierarchy is applied by default. For parameterised volumes in
	// the hierarchy, optimisation is -always- applied.

	thisG4Volume->setLogical(new G4LogicalVolume(thisG4Volume->getSolid(), thisMaterial, vname), verbosity);

	// material found, can build the logical volume
//	if(gui) {
//		// vis attributes
//	}



	return thisG4Volume->getLogical();
}









