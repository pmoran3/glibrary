// gparticle 
#include "gparticle.h"

// geant4
#include "G4ParticleTable.hh"
#include "G4Event.hh"


void Gparticle::shootParticle(G4GeneralParticleSource* particleGun, G4Event* anEvent) {

	auto particleDef = G4ParticleTable::GetParticleTable()->FindParticle(pid);
	particleGun->GetCurrentSource()->SetParticleDefinition(particleDef);


}
