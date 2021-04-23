#ifndef  GDYNAMIC_H
#define  GDYNAMIC_H 1

// mlibrary
#include "gdl.h"
#include "gtouchable.h"
#include "observables/gobservables.h"
#include "ghit.h"

// c++
#include <vector>
#include <bitset>
using namespace std;

// geant4
#include "G4Step.hh"

// properties of a sensitive detector, used in GTouchable and GHit.
// they are defined here so that the plugin can return it
class GSensitivePars {
public:
	// default constructor, set by base class
	GSensitivePars() : timeWindow(0), gridStartTime(0), hitBitSet("000000"), useTimeWindow(false) { }
	
	// constructor set by plugins
	GSensitivePars(double tw, double gst, int verbosity = 0) :
	timeWindow(tw),
	gridStartTime(gst),
	hitBitSet("000000"),
	useTimeWindow(false) {
		// if(verbosity > )
	}

public:
	// time window setter and getter
	void setUseTimeWindow()      {useTimeWindow = true;}    // false by default, change here
	bool doesItUseTimeWindow()   {return useTimeWindow;}

	// bitset setter and getter
	void setHitBitset(string hbs)   {    // define the hit bitset from a string.
		if(hbs.size() == NHITBITS) {
			hitBitSet = bitset<NHITBITS>(hbs);
		} else {
			hitBitSet = bitset<NHITBITS>("000000");
		}
	}
	bitset<NHITBITS> getHitBitSet() {return hitBitSet;}

private:
	double    timeWindow;         // electronic timewindow of the detector
	double    gridStartTime;      // defines the windows grid
	bitset<NHITBITS> hitBitSet;   // defines what information to be stored in the hit
	bool      useTimeWindow;      // decides if the hit definitions needs to use the time window

public:
	
	// for readout detectors, return the time cell
	inline int timeCell(double time) {
		return (int) (floor((time - gridStartTime)/timeWindow) + 1);
	}
	
	vector<string> showParameters() {
		vector<string> messages;
		messages.push_back(" Time Window: " + to_string(timeWindow));
		return messages;
	}
};

class GDynamic {

public:

	// change the GTouchable in sensitiveDetector::ProcessHit
	// by default the touchable is not changed
	// this function is loaded by plugin methods
	virtual vector<GTouchable*> processTouchable(GTouchable *gTouchID, G4Step* thisStep) {return { gTouchID } ;}

	// initialize sensitiveDetector parameters in sensitiveDetector::Initialize
	virtual void loadSensitivePars(int runno, string variation) {
	  gSensitiveParameters = new GSensitivePars();
	}

	// true information hit
	GObservables *trueInfoHit(GHit *ghit);
	GObservables *trueInfoPulse(GHit *ghit);
	
	// fill the observable object, one entry per hit
	virtual GObservables *digitizeHit(GHit *ghit) {return nullptr;}

	// fill the observable object, multiple entries per hit
	virtual GObservables *digitizePulse(GHit *ghit) {return nullptr;}

	// loads the calibration constants
	// return false for failure
	virtual bool loadConstants(int runno, string variation) { return false; }
	
	// logs the constants
	virtual vector<string> showConstants() { return  {" Please implement showConstants() in your plugin."}; }
	vector<string> showParameters()        { return gSensitiveParameters->showParameters();}
	
	// the implementation should always return true
	// this is used as sanity check that the DL is actually loaded
	virtual bool checkPlugin() { return false; }

	GSensitivePars *gSensitiveParameters;
	
	
	// method to dynamically load factories
	static GDynamic* instantiate(const dlhandle handle) {
				
		if (handle == nullptr) return nullptr;

		void *maker = dlsym(handle , "GDynamicFactory");

		if (maker == nullptr) return nullptr;

		typedef GDynamic* (*fptr)();

		// static_cast not allowed here
		// see http://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast
		// need to run the DLL GDynamicFactory function that returns the factory
		fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

		return func();
	}

};


#endif
