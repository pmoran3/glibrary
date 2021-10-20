// guts
#include "gutilities.h"
using namespace gutilities;

// gparticle
#include "gparticle.h"

// geant4
#include "G4ParticleTable.hh"
#include "G4Event.hh"


Gparticle::Gparticle(gparticle::JParticle jparticle) {
	pname        = jparticle.pname;
	pid          = jparticle.pid;
	multiplicity = jparticle.multiplicity;
	
	p = G4ThreeVector(
							getG4Number(jparticle.px, jparticle.punit),
							getG4Number(jparticle.py, jparticle.punit),
							getG4Number(jparticle.pz, jparticle.punit)
							);
	v = G4ThreeVector(
							getG4Number(jparticle.vx, jparticle.vunit),
							getG4Number(jparticle.vy, jparticle.vunit),
							getG4Number(jparticle.vz, jparticle.vunit)
							);



}


void Gparticle::shootParticle(G4GeneralParticleSource* particleGun, G4Event* anEvent) {

	auto particleDef = G4ParticleTable::GetParticleTable()->FindParticle(pid);
	particleGun->GetCurrentSource()->SetParticleDefinition(particleDef);




	
}
