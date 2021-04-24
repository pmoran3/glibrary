// gdata
#include "gDigitizedHit.h"

// gstring for the conventions and gexit
#include "gstring.h"

void GDigitizedHit::includeVariable(string varName, int var) {
	(*intObservables)[varName] = var;
}

