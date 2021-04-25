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
	// default constructor
	GEventData() {
		gLogConstruct("GEventData");
	}

	~GEventData() {
		gLogDestruct("GEventData");
		delete gheader;
	}

public:

	void setHeader(int n, int tid, int v = 0) {
		if ( gheader != nullptr) {
			delete gheader;
		}
		gheader = new GEventHeader(n, tid, v);
	}

private:

	GEventHeader *gheader = nullptr;
};


#endif
