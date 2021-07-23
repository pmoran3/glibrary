// guts
#include "gutilities.h"
using namespace gutilities;

// g4system
#include "g4systemConventions.h"
#include "g4objectsFactories/g4objectsFactory.h"


G4VSolid* G4ObjectsFactory::getSolidFromMap(string vname, map<string, G4Volume*> *g4s) const
{

	if(g4s->find(vname) != g4s->end()) {
		auto thisGVolume = (*g4s)[vname];
		return thisGVolume->getSolid();
	}

	return nullptr;
}

G4LogicalVolume* G4ObjectsFactory::getLogicalFromMap(string vname, map<string, G4Volume*> *g4s) const
{

	if(g4s->find(vname) != g4s->end()) {
		auto thisGVolume = (*g4s)[vname];
		return thisGVolume->getLogical();
	}

	return nullptr;
}

G4VPhysicalVolume* G4ObjectsFactory::getPhysicalFromMap(string vname, map<string, G4Volume*> *g4s) const
{

	if(g4s->find(vname) != g4s->end()) {
		auto thisGVolume = (*g4s)[vname];
		return thisGVolume->getPhysical();
	}

	return nullptr;
}

G4RotationMatrix* G4ObjectsFactory::getRotation(GVolume *s)
{
	G4RotationMatrix *rot = new G4RotationMatrix(G4ThreeVector(1, 0, 0),
																G4ThreeVector(0, 1, 0),
																G4ThreeVector(0, 0, 1));


	vector<string> rotDef = getStringVectorFromStringWithDelimiter(s->getRot(), ",");

	// default ordered rotation
	if(rotDef.size() == 3) {
		vector<double> rotPars = getG4NumbersFromStringVector(rotDef);
		rot->rotateX(rotPars[0]);
		rot->rotateY(rotPars[1]);
		rot->rotateZ(rotPars[2]);
		// custom ordered rotation
	} else if(rotDef.size() == 5) {
		if(rotDef[0] == "ordered:" || rotDef[0] == "Ordered:") {
			string order = rotDef[1];
			vector<double> rotPars = getG4NumbersFromStringVector({rotDef[2], rotDef[3], rotDef[4]});

			if(order == "xzy") {
				rot->rotateX(rotPars[0]);
				rot->rotateZ(rotPars[1]);
				rot->rotateY(rotPars[2]);
			} else if(order == "yxz") {
				rot->rotateY(rotPars[0]);
				rot->rotateX(rotPars[1]);
				rot->rotateZ(rotPars[2]);
			} else if(order == "yzx") {
				rot->rotateY(rotPars[0]);
				rot->rotateZ(rotPars[1]);
				rot->rotateX(rotPars[2]);
			} else if(order == "zxy") {
				rot->rotateZ(rotPars[0]);
				rot->rotateX(rotPars[1]);
				rot->rotateY(rotPars[2]);
			} else if(order == "zyx") {
				rot->rotateZ(rotPars[0]);
				rot->rotateY(rotPars[1]);
				rot->rotateX(rotPars[2]);
			} else {
				G4cerr << FATALERRORL << "ordered rotation <" << order << "> for " << s->getName() << " is wrong, it must be one of the following:"
				<< " xzy, yxz, yzx, zxy or zyx. Exiting." << G4endl;
				gexit(EC__G4WRONGORDEREDROTATION);
			}
		}
	}

	// tilt modifier (only xyz order)
	if(s->getTilt() != G4SYSTEMNOTAPPLICABLEENTRY) {
		vector<double> tiltVector = getG4NumbersFromString(s->getTilt());
		if(tiltVector.size() == 3) {
			rot->rotateX(tiltVector[0]);
			rot->rotateZ(tiltVector[1]);
			rot->rotateY(tiltVector[2]);
		}
	}
	return rot;
}

G4ThreeVector G4ObjectsFactory::getPosition(GVolume *s)
{
	G4ThreeVector pos(0,0,0);

	vector<double> posVector = getG4NumbersFromString(s->getPos());
	if(posVector.size() == 3) {
		pos.setX(posVector[0]);
		pos.setY(posVector[1]);
		pos.setZ(posVector[2]);
	}

	// shift modifier
	if(s->getShift() != G4SYSTEMNOTAPPLICABLEENTRY) {
		vector<double> shiftVector = getG4NumbersFromString(s->getShift());
		if(shiftVector.size() == 3) {
			G4ThreeVector shift(shiftVector[0], shiftVector[1], shiftVector[2]);
			pos = pos + shift;
		}
	}

	return pos;
}
