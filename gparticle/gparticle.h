#ifndef  GPARTICLE_H
#define  GPARTICLE_H  1

// geant4
#include "G4ThreeVector.hh"

// This class interfaces to the Geant4 General Particle Source
class  Gparticle
{


	// PDG Monte Carlo Particle Numbering Scheme:
	// https://pdg.lbl.gov/2019/reviews/rpp2019-rev-monte-carlo-numbering.pdf

private:

	int pid;
	G4ThreeVector p;
	G4ThreeVector v;


public:
	

};


#endif
