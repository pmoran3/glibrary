// gdata
#include "gEventData.h"

// c++
#include <iostream>
#include <thread>
using std::thread;


// emulation of a run of 10 events
int main(int argc, char* argv[])
{

	int nevents = 10;

	// a run is a collection of 10 events
	vector<GEventData*> *runData = new vector<GEventData*>;

	for (int evn = 1; evn <= nevents ; evn++ ) {

		// calling gheader with verbosity 1 for debugging purposes
		GEventHeader *gheader = new GEventHeader(evn, evn, 1);
		GEventData *eventData = new GEventData(gheader, 1);

		GDigitizedData *thisHit = new GDigitizedData();
		
		thisHit->includeVariable("crate",     evn);
		thisHit->includeVariable("slot",    2*evn);
		thisHit->includeVariable("channel", 3*evn);

		eventData->addDetectorDigitizedData("dc", thisHit);

		runData->push_back(eventData);
	}

	// we probably want to print events here 

	// now deleting events
	for (auto* edata: (*runData) ) {
		delete edata;
	}

	delete runData;

	return EXIT_SUCCESS;
}

