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
// 1st bit: energy deposited, time
// 2nd bit: global position, step length
// 3rd bit: local position
// 4th bit: track informations: momentum, total energy, vertex, pid, track id
// 5th bit: mother particle track information. This is created after the event
// 6th bit: meta information: magnetic field. process id name that created the particle
// 7th bit: optical photon only: wavelength, momentum, vertex, track id


#endif
