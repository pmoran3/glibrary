#ifndef  GPARTICLE_H
#define  GPARTICLE_H  1

// gparticle
#include "gparticleOptions.h"

// geant4
#include "G4ThreeVector.hh"
#include "G4ParticleGun.hh"

// This class interfaces to the Geant4 General Particle Source
class  Gparticle
{
public:

	Gparticle(gparticle::JParticle jparticle);


private:

	// PDG Monte Carlo Particle Numbering Scheme:
	// https://pdg.lbl.gov/2019/reviews/rpp2019-rev-monte-carlo-numbering.pdf
	string name;
	int pid;
	int multiplicity;

	// momentum
	float p;
	G4ThreeVector pdir;

	// vertex
	G4ThreeVector v;


public:

	void shootParticle(G4ParticleGun* particleGun, G4Event* anEvent);

};


#endif
