#ifndef  GDYNAMICDIGITIZATION_H
#define  GDYNAMICDIGITIZATION_H 1

// dynamic digitization
#include "greadoutSpecs.h"

// glibrary
#include "gdl.h"
#include "gtouchable.h"
#include "ghit.h"
#include "event/gDigitizedData.h"
#include "event/gTrueInfoData.h"
#include "gtranslationTable.h"

// c++
#include <vector>
#include <bitset>

// geant4
#include "G4Step.hh"

class GDynamicDigitization {

public:
	// abstract destructor
	virtual ~GDynamicDigitization() = default;

	// change the GTouchable in sensitiveDetector::ProcessHit
	// by default the touchable is not changed
	// this function is loaded by plugin methods
	// notice that this returns a vector of touchables, one g4step can produce multiple hits
	virtual vector<GTouchable*> processTouchable(GTouchable *gTouchID, G4Step* thisStep) {return { gTouchID } ;}

	// filter true information into GTrueInfoHit
	// this integrates all available information built in GHit::buildHitInfosForBit
	GTrueInfoData *collectTrueInformation(GHit *ghit, int hitn);

	// digitize true information into GDigitizedHit
	virtual GDigitizedData *digitizeHit(GHit *ghit, int hitn) {return nullptr;}

	// loads the digitization constants
	// return false for failure
	virtual bool loadConstants(int runno, string variation) { return false; }

	// loads the translation table
	// return false for failure
	virtual bool loadTT(int runno, string variation) { return false; }

	// this will set the ghit:
	// - chargeAtElectronics
	// - timeAtElectronics
	// and will update ghit's gtouchable to include the GElectronic using the translation table (hardware address crate/slot/channel)
	// this will exit with error if the TT is not defined, or if
	void chargeAndTimeAtHardware(GHit *ghit, float time, int q);

	// mandatory initialization of readout specs
	virtual bool defineReadoutSpecs() = 0;

	GReadoutSpecs *readoutSpecs = nullptr;
	GTranslationTable *translationTable = nullptr;

	// method to dynamically load factories
	static GDynamicDigitization* instantiate(const dlhandle handle) {
				
		if (handle == nullptr) return nullptr;

		void *maker = dlsym(handle , "GDynamicFactory");

		if (maker == nullptr) return nullptr;

		typedef GDynamicDigitization* (*fptr)();

		// static_cast not allowed here
		// see http://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast
		// need to run the DLL GDynamicFactory function that returns the factory
		fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

		return func();
	}

};


#endif
