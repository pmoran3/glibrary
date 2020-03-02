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

//! a GOption can be int, double, or string
enum GOptionType {
	isInt,
	isDouble,
	isString
};  // option type


/// \class GOVariable
/// <b> GOVariable (GOption Variable) </b>\n\n
/// A GOVariable is a single tuple containing a value (double, int or string), a description (string):\n
class GOVariable
{
private:
	GOptionType gtype;

	int valueI;       ///< double value
	double valueD;    ///< double value
	string valueS;    ///< string value

	string description;


public:

	double value() {
		if ( gtype == isDouble ) {
			return valueD;
		} else {
			// throw error here
			return 0;
		}
	}
    
};


// \class GOption
/// <b> GOption </b>\n\n
/// A GOption contains:\n
/// - a summary description\n
/// - a long description (help) that can span multiple lines\n
/// - a category (string) is used to add sections to the help command.\n
/// \author \n Maurizio Ungaro
/// \author mail: ungaro@jlab.org\n\n\n



template <typename T> class GOption
{
private:

	vector<GOVariable> gvariables; ///<

	string description;               ///< summary description
	string help;                      ///< a long description (help) that can span multiple lines
	string category;                  ///< help category -help will group all categories together

public:
	//! default constructor
	GOption() = default;

	//! default copy constructor
	GOption ( const GOption & ) = default;

	//! Sets a double type option and description
	GOption(string d,
			  string h,
			  string cat = "general") :
	description(d),
	help(h),
	category(cat) {

	}




};


#endif
