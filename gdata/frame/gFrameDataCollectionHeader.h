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
	GFrameDataCollectionHeader(long int fid, float fd, int v = 0) : frameID(fid), frameDuration(fd), verbosity(v) {

		if ( verbosity >= GVERBOSITY_DETAILS ) {
			string log = "GFrameHeader id " + to_string(frameID) + ", time: " + to_string(time_ns()) + "ns";
			gLogClassConstruct(log);
		}
	}

	~GFrameDataCollectionHeader() {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			string log = "GEventHeader id " + to_string(frameID);
			gLogDestruct(log);
		}
	}

private:

	long int frameID;
	float frameDuration;

	int verbosity;

	// will be needed when writing it out
	long int time_ns() const {return frameID*frameDuration;}
};






#endif
