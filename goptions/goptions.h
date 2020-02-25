#ifndef  GOPTIONS_H
#define  GOPTIONS_H  1

// doxygen
#include "doxy.h"

// conventions
#include "conventions.h"

// \class GOption
/// <b> GOption </b>\n\n
/// A GOption contains:\n
/// - a json object
/// - a title, used as a key in the option map\n
/// - a summary description\n
/// - a long description (help) that can span multiple lines\n
/// - a category (string) is used to add sections to the help command.\n
/// \author \n Maurizio Ungaro
/// \author mail: ungaro@jlab.org\n\n\n

#include "json.hpp"

class GOption
{
private:

	json j;

	string title;          ///< used as a key in the option map
	string description;    ///< summary description
	string help;           ///< a long description (help) that can span multiple lines
	string category;       ///< help category -help will group all categories together

public:
	//! default constructor
	GOption() = default;

	//! default copy constructor
	GOption ( const GOption & ) = default;

	//! Sets a double type option and description
	GOption(string t, string d, string d, string cat = "general", bool canRepeat = false) : type(isDouble), valueD(v) {
		valueS = "na";
		setUOption(t, cat, canRepeat);
	}


}


#endif
