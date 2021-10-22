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

	// assigned momentum and distributions
	float p;
	float delta_p;
	float theta;
	float phi;
	float delta_theta;
	float delta_phi;
	string thetaModel;  // 'ct' (default): cosTheta is uniform. 'flat': theta is uniform
	bool momentumGaussianSpread;  // true: gaussian around values, using the deltas as sigmas. false: uniform distribution in speficied range

	// assigned vertex and distributions
	G4ThreeVector v;
	G4ThreeVector delta_v;
	float delta_VR;
	bool vertexGaussianSpread;  // true: gaussian around values, using the deltas as sigmas. false: uniform distribution in speficied range


public:

	void shootParticle(G4ParticleGun* particleGun, G4Event* anEvent);


	// methods that uniformly distribute the particles
private:

	float randomize(float center, float delta, bool gaussianSPread);

	float         calculateMomentum();
	G4ThreeVector calculateBeamDirection();
	G4ThreeVector calculateVertex();


};


#endif
