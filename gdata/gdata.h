#ifndef  GDATA_H
#define  GDATA_H  1

// conventions
#include "gdataConventions.h"

// gdata
#include "gobservables/gdetectorObservables.h"

// c++
#include <vector>
#include <string>
using std::vector;
using std::string;

// glibrary
//#include "ghit.h"
#include "goptions.h"

class GHeader
{
public:
	GHeader(int g4evn, int tid, string rndm) : g4EventNumber(g4evn), threadID(tid) {
	}
	
	string getTimeStamp() {return timeStamp();}
	int getG4Evn()        {return g4EventNumber;}
	int getThreadID()     {return threadID;}

private:
	int g4EventNumber;
	int threadID;
	string g4randomNumber;  // PRAGMA TODO: not used yet. check feasibility
	string timeStamp();
};

class GEventData
{
public:
	GEventData(GHeader gh) : gheader(gh) {}
	
public:
	void addDetectorData(GDetectorObservables *detectorData) {
		detectorsData.push_back(detectorData);
	}
	
	int getDetectorDataSize() {
		return (int) detectorsData.size();
	}
	
	// access data
	vector<GDetectorObservables*> getDetectorsData() {return detectorsData;}
	GHeader getHeader() {return gheader;}
	
private:
	// all detectors
	vector<GDetectorObservables*> detectorsData;
	
	GHeader gheader;
	
	// PRAGMA TODO: headers, generators infos
};


#endif
