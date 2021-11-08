#ifndef  GFRAMEHEADER_H
#define  GFRAMEHEADER_H  1

// gdata
#include "gutsConventions.h"

// glibrary
#include "goptions.h"         // GVERBOSITY
#include "gutsConventions.h"  // gLogClassConstruct

// c++
#include <iostream>
using std::to_string;

class GFrameDataCollectionHeader
{
public:
	GFrameDataCollectionHeader(long int frameID_, float frameDuration_, int v = 0) : verbosity(v), frameID(frameID_), frameDuration(frameDuration_)  {
		
		if ( verbosity >= GVERBOSITY_DETAILS ) {
			string log = "GFrameHeader id " + to_string(frameID) + ", time: " + to_string(time_ns()) + "ns";
			gLogClassConstruct(log);
		}
	}
	
	~GFrameDataCollectionHeader() {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			string log = "GFrameHeader id " + to_string(frameID);
			gLogDestruct(log);
		}
	}
	
	// getters
	inline long int const getFrameID() const { return frameID; }
	inline long int const getTime() const { return time_ns(); }
	
	
private:
	
	int verbosity;
	
	long int frameID;
	float frameDuration;
	
	long int time_ns() const;
	
};






#endif
