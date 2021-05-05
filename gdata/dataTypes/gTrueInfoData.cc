// gdata
#include "gTrueInfoData.h"

// gstring for the conventions and gexit
#include "gstring.h"

void GTrueInfoData::includeVariable(string varName, float var) {
	(*trueInfo)[varName] = var;
}

