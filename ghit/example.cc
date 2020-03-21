// gtouchable
#include "gtouchable.h"

// ghit
#include "ghit.h"

// c++
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{

	GTouchable ctof(readout, {GIdentifier("paddle", 22)});

	// a bitset
	bitset<NHITBITS> hitBitSet("000000");

	// hit with null G4Step (not used)
	GHit *newHit = new GHit(&ctof, nullptr, hitBitSet, "scheme");

	newHit->addStepInfos(nullptr);

	return 1;
}
