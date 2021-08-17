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
// requirement: the variable names must all be different
class GDigitizedData {
	
public:

	void print();

	// public interface to add data to a hit
	void includeVariable(string vname, int value);
	void includeVariable(string vname, float value);
	void includeVariable(string vname, double value);

private:

	// the data map are keyd with the variable name
	map<string, int>    intObservables;
	map<string, float>  fltObservables;
	map<string, double> dblObservables;

	map<string, vector<int> >    intVObservables;
	map<string, vector<float> >  fltVObservables;
	map<string, vector<double> > dblVObservables;

};


#endif
