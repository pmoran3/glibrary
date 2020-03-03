// goptions 
#include "goptions.h"

//! constructor: add options to the group option map
GOptions:GOptions(int argc, char *argv[], vector<GOption> goptions)
{

	// first, parse jcards, including imports


	//

}


/*!

 \fn string GOptions::findJCard(int argc, char *argv[])

 Finds the configuration file (jcard). Returns "na' if not found.

 \param argc argv the program arguments
 \return The filename if a jcard was found. "na" otherwise
 */

string GOptions::findJCard(int argc, char *argv[])
{
	// finds gcard file as one of the argument
	// extension is .gcard
	for(int i=1; i<argc; i++) {

		string arg = argv[i];

		size_t pos = arg.find(".jcard");
		if(pos != string::npos) return arg;

	}

	return "na";
}



