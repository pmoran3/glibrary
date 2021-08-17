#ifndef  GHIT_H_CONVENTIONS
#define  GHIT_H_CONVENTIONS 1

// c++
#include <bitset>

// number of bits that defines a ghit.
#define NHITBITS 6
#define UNINITIALIZEDQUANTITY -1

using HitBitSet = std::bitset<NHITBITS> ;

// GHIT Bitset.
// Setting a bit will call the corresponding code in buildHitInfos
//
// Information always present:
// - local and global positions (G4ThreeVector)
// - energy deposited, time
//
// Toggle existance by bit
// 1st bit 000001: step length
// 2nd bit 000010: track informations: momentum, total energy, vertex, pid, track id
// 3rd bit 000100: mother particle track information. This is created after the event
// 4th bit 001000: meta information: magnetic field. process id name that created the particle
// 5th bit 010000: optical photon only: wavelength, momentum, vertex, track id


#endif
