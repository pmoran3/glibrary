#ifndef  GSTRING_H
#define  GSTRING_H  1

// doxygen
#include "doxy.h"

// conventions
#include "conventions.h"

// c++
#include <vector>
#include <string>
using namespace std;


namespace gstring
{
	//! Removes leading and trailing spaces
	string trimSpacesFromString(string);

	//! a vector of strings from a stringstream, space is delimiter
	vector<string> getStringVectorFromString(string);



};


#endif
