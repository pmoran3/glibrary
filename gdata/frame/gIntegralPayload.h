#ifndef  GINTEGRALPAYLOAD_H
#define  GINTEGRALPAYLOAD_H  1

// gdata
//#include "gutsConventions.h"

// glibrary
#include "goptions.h"         // GVERBOSITY
#include "gutsConventions.h"  // gLogClassConstruct

// c++
#include <iostream>
using std::to_string;

struct GIntegralPayload
{
public:
	GIntegralPayload(int c, int s, int h, int q, int v = 0) :  verbosity(v), crate(c), slot(s), channel(h), charge(q) {

		if ( verbosity >= GVERBOSITY_DETAILS ) {
			gLogClassConstruct("GIntegralPayload");
		}
	}

	~GIntegralPayload() {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogDestruct("GIntegralPayload");
		}
	}

private:
	int verbosity;

	int crate;
	int slot;
	int channel;
	int charge;

};

#endif

