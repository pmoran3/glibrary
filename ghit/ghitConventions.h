#ifndef  GHIT_H_CONVENTIONS
#define  GHIT_H_CONVENTIONS 1

// c++
#include <bitset>

// number of bits that defines a ghit.
#define NHITBITS 6

using HitBitSet = std::bitset<NHITBITS> ;

// GHIT Bitset.
// Setting a bit will call the corresponding code in buildHitInfos
//
// Information always present:
// - local and global positions (G4ThreeVector)
// - energy deposited, time
//
// Toggle existance by bit
// 1rd bit: step length
// 2th bit: track informations: momentum, total energy, vertex, pid, track id
// 3th bit: mother particle track information. This is created after the event
// 4th bit: meta information: magnetic field. process id name that created the particle
// 5th bit: optical photon only: wavelength, momentum, vertex, track id


#endif
