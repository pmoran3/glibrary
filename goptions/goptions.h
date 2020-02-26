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


// \class GOption
/// <b> GOption </b>\n\n
/// A GOption contains:\n
/// - a summary description\n
/// - a long description (help) that can span multiple lines\n
/// - a category (string) is used to add sections to the help command.\n
/// \author \n Maurizio Ungaro
/// \author mail: ungaro@jlab.org\n\n\n



class GOption
{
private:

	string description;    ///< summary description
	string help;           ///< a long description (help) that can span multiple lines
	string category;       ///< help category -help will group all categories together
	bool   groupable;      ///< false (default): option is unique. Command line overwrite gcard.
								  ///< true: the options in the command line can be repeated. The options are grouped in the json file

public:
	//! default constructor
	GOption() = default;

	//! default copy constructor
	GOption ( const GOption & ) = default;

	//! Sets a double type option and description
	GOption(string t, string d, string h, string oneLinerDefinition, string cat = "general", string group = "na") :
	description(d),
	help(h),
	category(cat) {

	}




};


#endif
