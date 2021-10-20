#ifndef  GPARTICLE_H
#define  GPARTICLE_H  1

// gparticle
#include "gparticleOptions.h"

// geant4
#include "G4ThreeVector.hh"
#include "G4GeneralParticleSource.hh"

// This class interfaces to the Geant4 General Particle Source
class  Gparticle
{
public:

	Gparticle(gparticle::JParticle jparticle);


private:

	// PDG Monte Carlo Particle Numbering Scheme:
	// https://pdg.lbl.gov/2019/reviews/rpp2019-rev-monte-carlo-numbering.pdf
	int pid;
	int multiplicity;
	string pname;
	G4ThreeVector p;
	G4ThreeVector v;


public:

	void shootParticle(G4GeneralParticleSource* particleGun, G4Event* anEvent);

};


#endif
