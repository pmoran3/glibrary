#ifndef  GDYNAMICDIGITIZATION_H
#define  GDYNAMICDIGITIZATION_H 1

// dynamic digitization
#include "greadoutSpecs.h"

// glibrary
#include "gdl.h"
#include "gtouchable.h"
#include "ghit.h"
#include "dataTypes/gDigitizedData.h"
#include "dataTypes/gTrueInfoData.h"

// c++
#include <vector>
#include <bitset>
using namespace std;

// geant4
#include "G4Step.hh"

class GDynamicDigitization {

public:

	// change the GTouchable in sensitiveDetector::ProcessHit
	// by default the touchable is not changed
	// this function is loaded by plugin methods
	// notice that this returns a vector of touchables, one g4step can produce multiple hits
	virtual vector<GTouchable*> processTouchable(GTouchable *gTouchID, G4Step* thisStep) {return { gTouchID } ;}


	// filter true information into GTrueInfoHit
	// this integrates all available information built in GHit::buildHitInfosForBit
	GTrueInfoData *collectTrueInformation(GHit *ghit);

	// digitize true information into GDigitizedHit
	virtual GDigitizedData *digitizeData(GHit *ghit) {return nullptr;}
	

	// loads the digitization constants
	// return false for failure
	//virtual bool loadConstants(int runno, string variation) { return false; }
	
	// logs the constants
	//virtual vector<string> showConstants() { return  {" Please implement showConstants() in your plugin."}; }
	//vector<string> showParameters()        { return gSensitiveParameters->showParameters();}

	GReadoutSpecs *readoutSpecs;

	// initialize readout specs in GSensitiveDetector constructor if it's a readout electronics
	// must be implemented in case the detector has readout
	//virtual void loadReadoutSpecs(int runno, string variation) = 0;

	
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
