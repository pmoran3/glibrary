#ifndef  GOBSERVABLES_H
#define  GOBSERVABLES_H  1

// gdata
#include "gdataConventions.h"

// c++
#include <vector>
#include <string>
using std::vector;
using std::string;

// types of abservables
enum GObservableType { gint_t, gfloat_t, gdouble_t, gstring_t};


// GObservables is a collection of variables related to a ghit.

// The collection includes multiple types.
// The observable variable index spans across the types. For example:
// [int, int, double, double, int, string]
// corresponds to having gTypeIndexes 1, 2, 10K, 20K, 3, 1M
// this way the variable at gTypeIndex 4 correspond to the second in the doubleVar vector.
//
// Let's say we define a GObservables as:
// - adc (int)
// - voltage (double)

// then the GDetectorObservables would contain vector of those (adc, voltage) pairs.
//
// the GDetectorObservables GObservables vector index can be either :
// - the hit index
// - the pulse index
//
class GObservables
{
public:
	GObservables() : unitsAssigned(false) { }
	
private:
	// in order to avoid carrying these vectors for every hit / pulse,
	// they are cleared once unitsAssigned becomes true
	bool unitsAssigned;
	vector<string> varName;
	vector<string> varUnit;

	// available types
	vector<int> intVar;
	vector<float> floatVar;
	vector<double> doubleVar;
	vector<string> stringVar;

	// index of the variable multiplied by its type multiplier
	vector<int> gTypeIndex;
	
	// record to retrieve varible type
	vector<GObservableType> gType;

	int getVariableIndex(int forIndex);
	
public:
	bool areUnitsAssigned() {return unitsAssigned;}

	// clear the name and description. We do not need to carry those around
	void clearNamesAndUnits() {
		varName.clear();
		varUnit.clear();
		unitsAssigned = true;
	}

	vector<string> getName() {return varName;}
	vector<string> getUnit() {return varUnit;}

	// add variable value
	void addObservable(double var, string varName, string vunit);
	void addObservable(   int var, string varName, string vunit);
	void addObservable(string var, string varName, string vunit);
	void addObservable( float var, string varName, string vunit);
	
	// add variable name, description
	void addObservableAndUnit(string n, string desc);
	
	int    getIntVarAtIndex(   int i) {return intVar[   getVariableIndex(i)];}
	float  getFloatVarAtIndex( int i) {return floatVar[ getVariableIndex(i)];}
	double getDoubleVarAtIndex(int i) {return doubleVar[getVariableIndex(i)];}
	string getStringVarAtIndex(int i) {return stringVar[getVariableIndex(i)];}

	size_t getNumberOfObservables() {return gTypeIndex.size();}
	
	GObservableType getTypeAtIndex(int i) {return gType[i];}
};


#endif
