#ifndef GTRUEINFOHIT_H
#define GTRUEINFOHIT_H 1

#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;

// glibrary
#include "ghit.h"

// data for a single bu
class GTrueInfoData {
	
public:
	GTrueInfoData(GHit *ghit);
	vector<GIdentifier> getIdentity() const {return gidentity;}

	void includeVariable(string varName, float var);
	inline map<string, float> getVariablesMap() const {return trueInfoVariablesMap;}

private:
	// the data map are keyd with the variable name
	map<string, float> trueInfoVariablesMap ;
	vector<GIdentifier> gidentity;

};


#endif
