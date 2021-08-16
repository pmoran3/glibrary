// gdata
#include "gTrueInfoData.h"

// gutilities for the conventions and gexit
#include "gutilities.h"

void GTrueInfoData::includeVariable(string varName, float var) {
	trueInfoVariablesMap[varName] = var;
}

