// gdata
#include "gTrueInfoSteps.h"

// gstring for the conventions and gexit
#include "gstring.h"

void GTrueInfoSteps::includeVariable(string varName, vector<float> steps) {
	(*hitSteps)[varName] = steps;
}

