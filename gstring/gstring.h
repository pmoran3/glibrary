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

//! adds characters to a word to fill its digits up to ndigits
string fillDigits(string word, string c, int ndigits);

//! gets a g4number from a string that contains units
double getG4Number(string input, bool warnIfNotUnit = false);

//! gets a vector of g4numbers from a vector of strings containing units
vector<double> getG4NumbersFromStringVector(vector<string> vstring, bool warnIfNotUnit = false);

//! gets a vector of g4numbers from a strings containing units
vector<double> getG4NumbersFromString(string vstring, bool warnIfNotUnit = false);

//! parse a file, remove comments (starting with commentChars) and return the pure JSON string
string parseFileAndRemoveComments(string filename, string commentChars = "#");

};


#endif
