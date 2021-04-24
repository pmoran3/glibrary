#ifndef GTRUEINFOSTEPS_H
#define GTRUEINFOSTEPS_H 1

#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;


class GTrueInfoSteps {
	
public:

	void includeVariable(string varName, vector<float> steps);

	// called at the beginning of the event
	inline void prepeareHit() {
		hitSteps->clear();
	}


private:
	map<string, vector<float>>  *hitSteps = nullptr;

};




#endif
