// gdata
#include "gTrueInfoData.h"

// gutilities for the conventions and gexit
#include "gutilities.h"

GTrueInfoData::GTrueInfoData(GHit *ghit) {
	gidentity = ghit->getGID();
}

void GTrueInfoData::includeVariable(string varName, float var) {
	trueInfoVariablesMap[varName] = var;
}

