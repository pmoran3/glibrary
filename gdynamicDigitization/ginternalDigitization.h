#ifndef GINTERNALDIGITIZATION
#define GINTERNALDIGITIZATION 1

// glibrary
#include "gdynamicdigitization.h"
#include "gutsConventions.h"

class GFluxDigitization : public GDynamicDigitization {

public:

	// mandatory readout specs definitions
	bool defineReadoutSpecs();

	// digitized the hit
	GDigitizedData* digitizeHit(GHit *ghit, int hitn);

};

class GParticleCounterDigitization : public GDynamicDigitization {

public:

	// mandatory readout specs definitions
	bool defineReadoutSpecs();

	// digitized the hit
	GDigitizedData* digitizeHit(GHit *ghit, int hitn);

};


class GDosimeterDigitization : public GDynamicDigitization {

public:

	// mandatory readout specs definitions
	bool defineReadoutSpecs();

	// digitized the hit
	GDigitizedData* digitizeHit(GHit *ghit, int hitn);

};


#endif


