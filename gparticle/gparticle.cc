// guts
#include "gutilities.h"
using namespace gutilities;

// gparticle
#include "gparticle.h"
#include "gparticleConventions.h"

// geant4
#include "G4ParticleTable.hh"
#include "G4Event.hh"

// c++
using namespace std;

Gparticle::Gparticle(gparticle::JParticle jparticle) {

	name         = jparticle.pname;
	pid          = jparticle.pid;
	multiplicity = jparticle.multiplicity;
	p            = getG4Number(jparticle.p, jparticle.punit);

	float thetaRad = getG4Number(jparticle.theta, jparticle.aunit)/CLHEP::rad;
	float phiRad   = getG4Number(jparticle.phi, jparticle.aunit)/CLHEP::rad;

	pdir = G4ThreeVector(
								cos(phiRad)*sin(thetaRad),
								sin(phiRad)*sin(thetaRad),
								cos(thetaRad)
								);

	v = G4ThreeVector(
							getG4Number(jparticle.vx, jparticle.vunit),
							getG4Number(jparticle.vy, jparticle.vunit),
							getG4Number(jparticle.vz, jparticle.vunit)
							);



}

#include "G4UImanager.hh"


// for G4GeneralParticleSource API check:
// https://geant4.kek.jp/lxr/source/event/include/G4ParticleGun.hh
// https://geant4.kek.jp/lxr/source/event/src/G4ParticleGun.cc
void Gparticle::shootParticle(G4ParticleGun* particleGun, G4Event* anEvent) {

	auto particleDef = G4ParticleTable::GetParticleTable()->FindParticle(name);

	if ( particleDef ) {


		particleGun->SetParticleDefinition(particleDef);
		particleGun->SetParticleEnergy(p);
		particleGun->SetParticleMomentumDirection(pdir);
		particleGun->SetParticlePosition(v);



	

		for ( int i=0; i<multiplicity; i++) {
			particleGun->GeneratePrimaryVertex(anEvent);
		}

	} else {
		cerr << FATALERRORL << " particle " << name << " not found in G4ParticleTable." << endl;
		gexit(EC__GGPARTICLENOTFOUND);
	}







	
}
