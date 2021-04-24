#ifndef GDIGITIZEDHIT_H
#define GDIGITIZEDHIT_H 1


// observable types include int, float, double,
#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;



// in each hit, the digitization can produce single values or vectors of values
// the only condition is that the variable names must all be different
class GDigitizedHit {
	
public:

	void includeVariable(string varName, int var);

	// called at the beginning of the event
	inline void prepeareHit() {
		
		intObservables->clear();
		fltObservables->clear();
		dblObservables->clear();

		intVObservables->clear();
		fltVObservables->clear();
		dblVObservables->clear();
	}


private:

	// the data map are keyd with the variable name
	map<string, int>    *intObservables = nullptr;
	map<string, float>  *fltObservables = nullptr;
	map<string, double> *dblObservables = nullptr;

	map<string, vector<int>>    *intVObservables = nullptr;
	map<string, vector<float>>  *fltVObservables = nullptr;
	map<string, vector<double>> *dblVObservables = nullptr;

};


#endif
