#ifndef  GEVENTDATA_H
#define  GEVENTDATA_H  1

// conventions
#include "gdataConventions.h"


// c++
#include <vector>
#include <string>
using std::vector;
using std::string;

// glibrary
#include "goptions.h"


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
	
	GEventHeader gHeader;
	
	// PRAGMA TODO: headers, generators infos
};


#endif
