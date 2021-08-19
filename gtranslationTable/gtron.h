#ifndef GELECTRONIC_H
#define GELECTRONIC_H  1

#include <ostream>

struct GElectronic {

	GElectronic(int c, int s, int ch, int m) : crate(c), slot(s), channel(ch), mode(m) {}
	// empty constructor needed because of the map declaration in the translation table
	GElectronic() : crate(0), slot(0), channel(0), mode(0) {}

private:
	int crate;
	int slot;
	int channel;

	// GElectronic comparison:
	// mode == 0: crate
	// mode == 1: crate, slot
	// mode == 2: crate, slot, channel
	// for example, if mode = 1:
	// 3,3,1 is the same as 3,3,4
	// in mode 2 the above would not be the same
	int mode;

	//! overloading the << operator
	friend std::ostream &operator<<(std::ostream &stream, GElectronic ge);

	//  Overloaded "!=": comparing idValue
	bool operator == (const GElectronic& ge) const; 

};


#endif
