// g4system
#include "cadSystemFactory.h"

// Cadmesh single header library, @tag 2.0.3
// https://github.com/christopherpoole/CADMesh
// notice I made some changes to silence the warnings:
// - added virtual destructor on line 342,
// - made destructor virtual on line 400
#include "CADMesh.hh"

G4VSolid* G4CadSystemFactory::buildSolid(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s)
{

	string vname    = s->getName();
	string vMapname = s->getMapName();
	bool verbosity = getVerbosity(gopt, vname);

	// check dependencies first
	if(!checkSolidDependencies(verbosity, s, g4s)) return nullptr;

	// if the g4volume doesn't exist, create one and add it to the map
	G4Volume *thisG4Volume = nullptr;

	// check if g4s already exists
	if(g4s->find(vMapname) != g4s->end()) {
		thisG4Volume = (*g4s)[vMapname];
		// if the solid is already built, returning it
		if (thisG4Volume->getSolid() != nullptr) return thisG4Volume->getSolid();
	} else {
		thisG4Volume = new G4Volume();
		// adding volume to the map
		(*g4s)[vMapname] = thisG4Volume;
	}

	string fileName  = s->getDescription();
	auto extension = getStringVectorFromStringWithDelimiter(fileName, ".").back();


	if ( extension == "ply" ) {
//		auto mesh = CADMesh::TessellatedMesh::FromPLY(fileName);
//		mesh->SetScale(CLHEP::mm);
//		mesh->SetReverse(false);
//
//		thisG4Volume->setSolid(mesh->GetSolid(), verbosity);
//		return thisG4Volume->getSolid();

	} else if ( extension == "stl" ) {
//		auto mesh = CADMesh::TessellatedMesh::FromSTL(fileName);
//		mesh->SetScale(CLHEP::mm);
//		mesh->SetReverse(false);
//
//		thisG4Volume->setSolid(mesh->GetSolid(), verbosity);
//		return thisG4Volume->getSolid();


		auto mesh = new CADMesh((char *) fileName.c_str());
//		auto mesh = new CADMesh((char *) filename.c_str());
		mesh->SetScale(CLHEP::mm);
		mesh->SetReverse(false);

		// solid
	//	G4VSolid *cad_solid = mesh->TessellatedMesh();
		thisG4Volume->setSolid(mesh->TessellatedMesh(), verbosity);
		return thisG4Volume->getSolid();


	}

	
	return nullptr;

}
