#ifndef  GEVENTDATA_H
#define  GEVENTDATA_H  1

// conventions
#include "gdataConventions.h"

// c++
#include <vector>
using std::vector;

// gdata
#include "gEventHeader.h"

// glibrary
#include "goptions.h"
#include "gstringConventions.h"


class GEventData
{
public:
	// construct event data using a GEventHeader
	GEventData(GEventHeader* header, int v = 0 ) : gheader(header), verbosity(v) {
		if ( verbosity ) {
			gLogConstruct("GEventData");
		}
	}

	~GEventData() {
		if ( verbosity ) {
			gLogDestruct("GEventData");
		}
		delete gheader;
	}

public:


private:
	GEventHeader *gheader = nullptr;
	int verbosity;
};


#endif
