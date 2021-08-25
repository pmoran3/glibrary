#ifndef  GEVENTHEADER_H
#define  GEVENTHEADER_H  1

// gdata
#include "gdataConventions.h"

// glibrary
#include "goptions.h"         // GVERBOSITY
#include "gutsConventions.h"  // gLogClassConstruct

// c++
#include <iostream>
using std::cout;
using std::endl;
using std::to_string;

class GEventDataCollectionHeader
{
public:
	// the event number comes from aEvent->GetEventID(), that is why it's called g4EventNumber here
	GEventDataCollectionHeader(int n, int tid, int v = 0) : g4localEventNumber(n), threadID(tid), verbosity(v) {

		timeStamp = assignTimeStamp();

		if ( verbosity >= GVERBOSITY_DETAILS ) {
			string log = "GEventHeader evn " + to_string(g4localEventNumber);
			gLogClassConstruct(log);
			print();
		}
	}

	~GEventDataCollectionHeader() {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			string log = "GEventHeader evn " + to_string(g4localEventNumber);
			gLogDestruct(log);
		}
	}
	
	string getTimeStamp() {return timeStamp;}
	inline int const getG4LocalEvn()  const {return g4localEventNumber;}
	inline int const getThreadID()    const {return threadID;}

	void print() {
		cout << CONSTRUCTORLOG <<  " Event header: " << endl;
		cout << TPOINTITEM <<  " Event Number:  "    << g4localEventNumber << endl;
		cout << TPOINTITEM <<  " Thread ID:  "       << threadID  << endl;
		cout << TPOINTITEM <<  " Time Stamp:  "      << timeStamp << endl;
	}

private:
	int g4localEventNumber;
	int threadID;
	int verbosity;

	string assignTimeStamp();
	string timeStamp;
};


#endif
