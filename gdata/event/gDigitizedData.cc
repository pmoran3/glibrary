// gdata
#include "gDigitizedData.h"

// gutilities for the conventions and gexit
#include "gutilities.h"


GDigitizedData::GDigitizedData(GHit *ghit) {
	gidentity = ghit->getGID();
}

void GDigitizedData::includeVariable(string vname, int value) {
	intObservablesMap[vname] = value;
}

void GDigitizedData::includeVariable(string vname, float value) {
	fltObservablesMap[vname] = value;
}

