// gdata
#include "gTrueInfoHit.h"

// gstring for the conventions and gexit
#include "gstring.h"

void GTrueInfoHit::includeVariable(string varName, float var) {
	(*trueInfo)[varName] = var;
}

