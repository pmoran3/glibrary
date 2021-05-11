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

class GEventHeader
{
public:
	GEventHeader(int n, int tid, int v = 0) : evn(n), threadID(tid), verbosity(v) {

		timeStamp = assignTimeStamp();

		if ( verbosity ) {
			string log = "GEventHeader evn " + to_string(evn);
			gLogClassConstruct(log);
			print();
		}
	}

	~GEventHeader() {
		if ( verbosity ) {
			string log = "GEventHeader evn " + to_string(evn);
			gLogDestruct(log);
		}
	}
	
	string getTimeStamp() {return timeStamp;}
	int getEvn()          {return evn;}
	int getThreadID()     {return threadID;}

	void print() {
		cout << CONSTRUCTORLOG <<  " Event header: " << endl;
		cout << TPOINTITEM <<  " Event Number:  "    << evn << endl;
		cout << TPOINTITEM <<  " Thread ID:  "       << threadID  << endl;
		cout << TPOINTITEM <<  " Time Stamp:  "      << timeStamp << endl;
	}

private:
	int evn;
	int threadID;
	int verbosity;

	string g4randomNumber;  // PRAGMA TODO: not used yet. check feasibility
	string assignTimeStamp();
	string timeStamp;
};


#endif
