// guts
#include "gutilities.h"
using namespace gutilities;

// gparticle
#include "gparticle.h"
#include "gparticleConventions.h"

// geant4
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "Randomize.hh"

// c++
using namespace std;

Gparticle::Gparticle(gparticle::JParticle jparticle) {

	name         = jparticle.pname;
	pid          = jparticle.pid;
	multiplicity = jparticle.multiplicity;
	thetaModel   = jparticle.thetaModel;

	p     = getG4Number(jparticle.p,     jparticle.punit);
	theta = getG4Number(jparticle.theta, jparticle.aunit);
	phi   = getG4Number(jparticle.phi,   jparticle.aunit);

	delta_p     = getG4Number(jparticle.delta_p,     jparticle.punit);
	delta_theta = getG4Number(jparticle.delta_theta, jparticle.aunit);
	delta_phi   = getG4Number(jparticle.delta_phi,   jparticle.aunit);


	if (jparticle.randomMomentumModel == "gaussian") {
		momentumGaussianSpread = true;
	} else {
		momentumGaussianSpread = false;
	}
	
	if (jparticle.randomVertexModel == "gaussian") {
		vertexGaussianSpread = true;
	} else {
		vertexGaussianSpread = false;
	}

	v = G4ThreeVector(
							getG4Number(jparticle.vx, jparticle.vunit),
							getG4Number(jparticle.vy, jparticle.vunit),
							getG4Number(jparticle.vz, jparticle.vunit)
							);

	delta_v = G4ThreeVector(
							getG4Number(jparticle.delta_vx, jparticle.vunit),
							getG4Number(jparticle.delta_vy, jparticle.vunit),
							getG4Number(jparticle.delta_vz, jparticle.vunit)
							);

	delta_VR = getG4Number(jparticle.delta_VR, jparticle.vunit);


}


// for G4GeneralParticleSource API check:
// https://geant4.kek.jp/lxr/source/event/include/G4ParticleGun.hh
// https://geant4.kek.jp/lxr/source/event/src/G4ParticleGun.cc
void Gparticle::shootParticle(G4ParticleGun* particleGun, G4Event* anEvent) {

	auto particleDef = G4ParticleTable::GetParticleTable()->FindParticle(name);

	if ( particleDef ) {

		particleGun->SetParticleDefinition(particleDef);

		for ( int i=0; i<multiplicity; i++) {

			particleGun->SetParticleMomentum(calculateMomentum());
			particleGun->SetParticleMomentumDirection(calculateBeamDirection());
			particleGun->SetParticlePosition(calculateVertex());
			particleGun->GeneratePrimaryVertex(anEvent);
		}

	} else {
		cerr << FATALERRORL << " particle " << name << " not found in G4ParticleTable." << endl;
		gexit(EC__GGPARTICLENOTFOUND);
	}


}


float Gparticle::calculateMomentum() {

	double pmev = randomize(p/CLHEP::MeV, delta_p/CLHEP::MeV, momentumGaussianSpread);

	return pmev;
}

G4ThreeVector Gparticle::calculateBeamDirection() {

	double thetaRad = 0;


	if (thetaModel == "ct") {
		thetaRad = acos(G4UniformRand()*(cos(theta/CLHEP::rad - delta_theta/CLHEP::rad) - cos(theta/CLHEP::rad + delta_theta/CLHEP::rad))
							 + cos(theta/CLHEP::rad + delta_theta/CLHEP::rad)) / CLHEP::rad;

	} else if (thetaModel == "flat") {
		thetaRad =  randomize(theta/CLHEP::rad, delta_theta/CLHEP::rad, momentumGaussianSpread) ;
	} else {
		cerr << FATALERRORL << " thetaModel >" << thetaModel << "< not recognized." << endl;
		gexit(EC__GGPARTICLEWRONGTHETAMODEL);
	}

	double phiRad = randomize(phi/CLHEP::rad, delta_phi/CLHEP::rad, momentumGaussianSpread) ;


	G4ThreeVector pdir = G4ThreeVector(
								cos(phiRad)*sin(thetaRad),
								sin(phiRad)*sin(thetaRad),
								cos(thetaRad)
								);
	
	return pdir;
}

G4ThreeVector Gparticle::calculateVertex() {

	float x, y, z;

	if (delta_VR > 0 ) {
		float radius;
		do {
			x = randomize(0, delta_VR, vertexGaussianSpread);
			y = randomize(0, delta_VR, vertexGaussianSpread);
			z = randomize(0, delta_VR, vertexGaussianSpread);
			radius = x*x + y*y + z*z;
		} while(radius > delta_VR);

		x = x + v.x();
		y = y + v.y();
		z = z + v.z();

	} else {
		x = randomize(v.x(), delta_v.x(), vertexGaussianSpread);
		y = randomize(v.y(), delta_v.y(), vertexGaussianSpread);
		z = randomize(v.z(), delta_v.z(), vertexGaussianSpread);
	}


	G4ThreeVector vertex = G4ThreeVector(x, y, z);

	return vertex;
}



float Gparticle::randomize(float center, float delta, bool gaussianSPread) {
	if (gaussianSPread) {
		return G4RandGauss::shoot(center, delta);
	} else {
		return center + (2.0*G4UniformRand()-1.0)*delta;
	}
}

