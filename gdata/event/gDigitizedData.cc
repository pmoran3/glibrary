// gdata
#include "gDigitizedData.h"
#include "gdataConventions.h"

// gutilities for the conventions and gexit
#include "gutilities.h"


// the methods below filter out the streaming vars

map<string, int> const GDigitizedData::getIntObservablesMap() const {
	map<string, int> filteredIntObservablesMap;

	for ( auto [varName, value]: intObservablesMap) {
		if (validVarName(varName) ) {
			filteredIntObservablesMap[varName] = value;
		}
	}


	return filteredIntObservablesMap;
}
map<string, float> const GDigitizedData::getFltObservablesMap() const {
	map<string, float> filteredFltObservablesMap;

	for ( auto [varName, value]: fltObservablesMap) {
		if ( validVarName(varName) ) {
			filteredFltObservablesMap[varName] = value;
		}
	}

	return filteredFltObservablesMap;
}


// criteria for valid var name: it's not any of the streaming var
bool const GDigitizedData::validVarName(string varName) const {

	if (varName == CRATESTRINGID || varName == SLOTSTRINGID || varName == CHANNELSTRINGID || varName == CHARGEATELECTRONICS || varName == TIMEATELECTRONICS) {
		return false;
	}

	return true;
}

GDigitizedData::GDigitizedData(GHit *ghit) {
	gidentity = ghit->getGID();
}

void GDigitizedData::includeVariable(string vname, int value) {
	intObservablesMap[vname] = value;
}

void GDigitizedData::includeVariable(string vname, float value) {
	fltObservablesMap[vname] = value;
}

