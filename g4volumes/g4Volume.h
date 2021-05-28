#ifndef  G4VOLUME_H
#define  G4VOLUME_H 1


// geant4
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"


class G4Volume
{

public:
	G4Volume(G4VSolid* s = nullptr, G4LogicalVolume* l = nullptr, G4VPhysicalVolume* p = nullptr) :
	solidVolume(s), logicalVolume(l), physicalVolume(p) { ; }

public:
	G4VSolid*          getSolid()    const { if(solidVolume)    return solidVolume;    else return nullptr;}
	G4LogicalVolume*   getLogical()  const { if(logicalVolume)  return logicalVolume;  else return nullptr;}
	G4VPhysicalVolume* getPhysical() const { if(physicalVolume) return physicalVolume; else return nullptr;}

	void addSolid(G4VSolid* s, int verbosity=0);
	void addLogical(G4LogicalVolume* l, int verbosity=0);
	void addPhysical(G4VPhysicalVolume* p, int verbosity=0);

private:
	G4VSolid*             solidVolume;   ///< Solid
	G4LogicalVolume*    logicalVolume;   ///< Logical Volume
	G4VPhysicalVolume* physicalVolume;   ///< Physical Volume
};



#endif

