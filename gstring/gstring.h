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


namespace gstring {

//! Removes leading and trailing spaces
string trimSpacesFromString(string);

//! a vector of strings from a stringstream, space is delimiter
vector<string> getStringVectorFromString(string);

//! Replace all occurences of a char in string with a string
string replaceCharInStringWithChars(string input, string toReplace, string replacement);

// adds zeros to fill totDigits
string fillDigits(string word, string c, int ndigits);


};


#endif
