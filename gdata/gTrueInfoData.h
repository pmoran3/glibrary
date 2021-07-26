#ifndef GTRUEINFOHIT_H
#define GTRUEINFOHIT_H 1

#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;


class GTrueInfoData {
	
public:

	void includeVariable(string varName, float var);

	// called at the beginning of the event
	inline void prepeareHit() {
		trueInfo->clear();
	}

private:

	// the data map are keyd with the variable name
	map<string, float>  *trueInfo = nullptr;
};


#endif
