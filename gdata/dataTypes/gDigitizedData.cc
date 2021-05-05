// gdata
#include "gDigitizedData.h"

// gstring for the conventions and gexit
#include "gstring.h"

void GDigitizedData::includeVariable(string vname, int value) {
	intObservables[vname] = value;
}

void GDigitizedData::includeVariable(string vname, float value) {
	fltObservables[vname] = value;
}

void GDigitizedData::includeVariable(string vname, double value) {
	dblObservables[vname] = value;
}
