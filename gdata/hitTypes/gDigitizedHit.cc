// gdata
#include "gDigitizedHit.h"

// gstring for the conventions and gexit
#include "gstring.h"

void GDigitizedHit::includeVariable(string vname, int value) {
	intObservables[vname] = value;
}

void GDigitizedHit::includeVariable(string vname, float value) {
	fltObservables[vname] = value;
}

void GDigitizedHit::includeVariable(string vname, double value) {
	dblObservables[vname] = value;
}
