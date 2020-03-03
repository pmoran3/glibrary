#ifndef  GOPTIONS_H
#define  GOPTIONS_H  1

// doxygen
#include "doxy.h"

// conventions
#include "conventions.h"

// json parser
#include "json.hpp"
using namespace nlohmann;

// c++
#include <string>
using namespace std;

// to be filled by libraries utilizing goptions
namespace goptions {

}


////! a GOption can be int, double, or string
//enum GOptionType {
//	isInt,
//	isDouble,
//	isString
//};  // option type


///// \class GOVariable
///// <b> GOVariable (GOption Variable) </b>\n\n
///// A GOVariable is a single tuple containing a value (double, int or string), a description (string):\n
//class GOVariable
//{
//private:
//	GOptionType gtype;
//
//	int valueI;       ///< double value
//	double valueD;    ///< double value
//	string valueS;    ///< string value
//
//	string description;
//
//
//public:
//
//	double value() {
//		if ( gtype == isDouble ) {
//			return valueD;
//		} else {
//			// throw error here
//			return 0;
//		}
//	}
//
//};


// \class GOption
/// <b> GOption </b>\n\n
/// A GOption contains:\n
/// - a summary description\n
/// - a long description (help) that can span multiple lines\n
/// - a category (string) is used to add sections to the help command.\n
/// \author \n Maurizio Ungaro
/// \author mail: ungaro@jlab.org\n\n\n

//! a GOption can be int, double, or string
enum GVerbosity {
	silent,
	summary,
	details,
	all
};  // option type



class GOption
{
private:

	string description;    ///< summary description. This is used in the search.
	string group;          ///< if an option belongs to a group, it can be repeated.
	GVerbosity verbosity;  ///< option verbosiry

	// the json contains the verbosity (defaulted at silent) and array of these objects:
	// { "tag": "tagname", "description": "tag description", "default": default value}
	// For example:
	//
	json joption;

public:

	//! default constructor
	GOption() = default;

	//! default copy constructor
	GOption ( const GOption & ) = default;

	//! constructor using a json object
	GOption(string d, json j, string g = "general"): description(d), joption(j), group(g) { }

};


class GOptions
{
public:
	//! constructor - ignore is optional
	GOptions(int argc, char *argv[], vector<GOption> goptions);

private:

	//! GOptions group map
	map<string, vector<GOption>> optionsMap;

	//! finds jcards
	string findJCard(int argc, char *argv[]);  ///< finds a configuration file (jcard). Returns "na' if not found.
	int parseJCard(string file);               ///< parse the jcard in the GOptions map


};




#endif
