// gdata
#include "gDigitizedData.h"

// gutilities for the conventions and gexit
#include "gutilities.h"

void GDigitizedData::includeVariable(string vname, int value) {
	intObservables[vname] = value;
}

void GDigitizedData::includeVariable(string vname, float value) {
	fltObservables[vname] = value;
}

void GDigitizedData::includeVariable(string vname, double value) {
	dblObservables[vname] = value;
}
