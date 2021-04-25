#ifndef  GEVENTHEADER_H
#define  GEVENTHEADER_H  1

//// c++
//#include <vector>
//using std::vector;
//using std::string;

// gdata
#include "gdataConventions.h"

// glibrary
#include "goptions.h"

class GEventHeader
{
public:
	GEventHeader(int n, int tid, int v = 0) : evn(n), threadID(tid), verbosity(v) {
		timeStamp = assignTimeStamp();

		if ( verbosity ) {
			cout << GDATALOGITEM <<  " Setting header: " << endl;
			cout << TPOINTITEM <<  " Event Number:  "    << evn << endl;
			cout << TPOINTITEM <<  " Thread ID:  "       << threadID  << endl;
			cout << TPOINTITEM <<  " Time Stamp:  "      << timeStamp << endl;
		}
	}
	
	string getTimeStamp() {return timeStamp();}
	int getEvn()          {return g4EventNumber;}
	int getThreadID()     {return threadID;}

private:
	int evn;
	int threadID;
	int verbosity;

	string g4randomNumber;  // PRAGMA TODO: not used yet. check feasibility
	string assignTimeStamp();
	string timeStamp;
};


#endif
