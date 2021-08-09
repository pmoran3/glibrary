// g4system
#include "g4NativeObjectsFactory.h"

// glibrary
#include "gutilities.h"
using namespace gutilities;

// geant4
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4CutTubs.hh"
#include "G4Cons.hh"
#include "G4Para.hh"
#include "G4Trd.hh"
#include "G4Polycone.hh"


G4VSolid* G4NativeSystemFactory::buildSolid(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s)
{
	string vname = s->getName();
	bool verbosity = getVerbosity(gopt, vname);

	// check dependencies first
	if(!checkSolidDependencies(verbosity, s, g4s)) return nullptr;

	// if the g4volume doesn't exist, create one and add it to the map
	G4Volume *thisG4Volume = nullptr;

	// check if g4s already exists
	if(g4s->find(vname) != g4s->end()) {
		thisG4Volume = (*g4s)[vname];
		// if the solid is already built, returning it
		if (thisG4Volume->getSolid() != nullptr) return thisG4Volume->getSolid();
	} else {
		thisG4Volume = new G4Volume();
		// adding volume to the map
		(*g4s)[vname] = thisG4Volume;
	}


	// the order of these objects is the same as on the geant4 website
	// https://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch04.html

	// check and get parameters
	vector<double> pars = checkAndReturnParameters(s);

	string type = s->getType();

	if(type == "G4Box") {
		thisG4Volume->setSolid(new G4Box(vname,      ///< name
													pars[0],    ///< half length in X
													pars[1],    ///< half length in Y
													pars[2]     ///< half length in Z
													), verbosity
									  );

		return thisG4Volume->getSolid();

	} else 	if(type == "G4Tubs") {
		thisG4Volume->setSolid(new G4Tubs(vname,     ///< name
													 pars[0],   ///< Inner radius
													 pars[1],   ///< Outer radius
													 pars[2],   ///< Half length in z
													 pars[3],   ///< Starting phi angle
													 pars[4]    ///< Delta Phi angle
													 ), verbosity
									  );

		return thisG4Volume->getSolid();

	} else 	if(type == "G4CutTubs") {
		thisG4Volume->setSolid(new G4CutTubs(vname,     ///< name
														 pars[0],   ///< Inner radius
														 pars[1],   ///< Outer radius
														 pars[2],   ///< Half length in z
														 pars[3],   ///< Starting phi angle
														 pars[4],   ///< Delta Phi angle
														 G4ThreeVector(pars[5], pars[6], pars[7]),    ///< Outside Normal at -z
														 G4ThreeVector(pars[8], pars[9], pars[10])    ///< Outside Normal at +z
														 ), verbosity
									  );

		return thisG4Volume->getSolid();

	} else 	if(type == "G4Cons") {
		thisG4Volume->setSolid(new G4Cons(vname,     ///< name
													 pars[0],   ///< Inside radius at -pDz
													 pars[1],   ///< Outside radius at -pDz
													 pars[2],   ///< Inside radius at +pDz
													 pars[3],   ///< Outside radius at +pDz
													 pars[4],   ///< Half length in z
													 pars[5],   ///< Starting phi angle
													 pars[6]    ///< Delta Phi angle
													 ), verbosity
									  );

		return thisG4Volume->getSolid();

	} else 	if(type == "G4Para") {
		thisG4Volume->setSolid(new G4Para(vname,     ///< name
													 pars[0],   ///< Half length in x
													 pars[1],   ///< Half length in y
													 pars[2],   ///< Half length in z
													 pars[3],   ///< Angle formed by the y axis and by the plane joining the centre of the faces parallel to the z-x plane at -dy and +dy
													 pars[4],   ///< Polar angle of the line joining the centres of the faces at -dz and +dz in z
													 pars[5]    ///< Azimuthal angle of the line joining the centres of the faces at -dz and +dz in z
													 ), verbosity
									  );

		return thisG4Volume->getSolid();

	} else 	if(type == "G4Trd") {
		thisG4Volume->setSolid(new G4Trd(vname,     ///< name
													pars[0],   ///< Half-length along x at the surface positioned at -dz
													pars[1],   ///< Half-length along x at the surface positioned at +dz
													pars[2],   ///< Half-length along y at the surface positioned at -dz
													pars[3],   ///< Half-length along y at the surface positioned at +dz
													pars[4]    ///< Half-length along z axis
													), verbosity
									  );
		return thisG4Volume->getSolid();

	} else if(type == "G4Polycone") {
		// see https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomSolids.html

		double phistart = pars[0];
		double phitotal = pars[1];
		int zplanes    = (int) pars[2];

		double* zPlane = new double[zplanes];
		double* rInner = new double[zplanes];
		double* rOuter = new double[zplanes];

		for(int zpl=0; zpl<zplanes; zpl++) {
			zPlane[zpl] = pars[3 + 0*zplanes + zpl] ;
			rInner[zpl] = pars[3 + 1*zplanes + zpl] ;
			rOuter[zpl] = pars[3 + 2*zplanes + zpl] ;
		}

		thisG4Volume->setSolid(new G4Polycone(vname,          ///< name
														  phistart,       ///< Initial Phi starting angle
														  phitotal,       ///< Total Phi angle
														  zplanes,        ///< Number of z planes
														  zPlane,         ///< z coordinate of corners
														  rInner,         ///< Tangent distance to inner surface
														  rOuter          ///< Tangent distance to outer surface, verbosity
														  ), verbosity
									  );

		return thisG4Volume->getSolid();
	} else {
		G4cerr << " " << vname << " solid " << type << " uknown! " << G4endl;
	}

	// if we are at this point the solid is not built
	if(verbosity) {
		G4cout << " " << vname << " solid is not built." << G4endl;
	}

	return nullptr;
}





