#ifndef  GEVENTHEADER_H
#define  GEVENTHEADER_H  1

//// c++
#include <iostream>
using std::cout;
using std::endl;
using std::to_string;

// gdata
#include "gdataConventions.h"

// glibrary
#include "goptions.h"
#include "gutsConventions.h"

class GEventDataCollectionHeader
{
public:
	// the event number comes from aEvent->GetEventID(), that is why it's called g4EventNumber here
	GEventDataCollectionHeader(int n, int tid, int v = 0) : g4EventNumber(n), threadID(tid), verbosity(v) {

		timeStamp = assignTimeStamp();

		if ( verbosity >= GVERBOSITY_DETAILS ) {
			string log = "GEventHeader evn " + to_string(g4EventNumber);
			gLogClassConstruct(log);
			print();
		}
	}

	~GEventDataCollectionHeader() {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			string log = "GEventHeader evn " + to_string(g4EventNumber);
			gLogDestruct(log);
		}
	}
	
	string getTimeStamp() {return timeStamp;}
	int getG4Evn()        {return g4EventNumber;}
	int getThreadID()     {return threadID;}

	void print() {
		cout << CONSTRUCTORLOG <<  " Event header: " << endl;
		cout << TPOINTITEM <<  " Event Number:  "    << g4EventNumber << endl;
		cout << TPOINTITEM <<  " Thread ID:  "       << threadID  << endl;
		cout << TPOINTITEM <<  " Time Stamp:  "      << timeStamp << endl;
	}

private:
	int g4EventNumber;
	int threadID;
	int verbosity;

	string g4randomNumber;  // PRAGMA TODO: not used yet. check feasibility
	string assignTimeStamp();
	string timeStamp;
};


#endif
