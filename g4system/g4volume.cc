// g4volume
#include "g4systemConventions.h"
#include "g4volume.h"

// glibrary
#include "goptionsConventions.h"

void G4Volume::setSolid(G4VSolid* s, int verbosity)
{
	solidVolume = s;

	if(verbosity == GVERBOSITY_DETAILS) {
		G4cout << G4SYSTEMLOGHEADER << "Geant4 Solid created for " << solidVolume->GetName() << "." << G4endl;
	}
}

void G4Volume::setLogical(G4LogicalVolume* l, int verbosity)
{
	logicalVolume = l;

	if(verbosity == GVERBOSITY_DETAILS) {
		G4cout << G4SYSTEMLOGHEADER << "Geant4 Logical created for " << logicalVolume->GetName() << "." << G4endl;
	}
}

void G4Volume::setPhysical(G4VPhysicalVolume* p, int verbosity)
{
	physicalVolume = p;

	if(verbosity == GVERBOSITY_DETAILS) {
		G4cout << G4SYSTEMLOGHEADER << "Geant4 Physical created for " << p->GetName() << "." << G4endl;
	}
}

