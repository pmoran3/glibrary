#ifndef DOXYGEN_SHOULD_SKIP_THIS /* DOXYGEN_SHOULD_SKIP_THIS */

// goptions
#include "goptions.h"

// c++
#include <iostream>
using namespace std;


// returns array of options definitions
vector<GOption> defineOptions()
{
	vector<GOption> goptions;

	// run option
	// not groupable
	// no help, just description
	json jsonRunOption = {
		{GNAME, "runno"},
		{GDESC, "Run number"},
		{GDFLT, 11}
	};

	goptions.push_back(GOption(jsonRunOption));

	// useGui option
	// not groupable
	// no help, just description
	json jsonGuiOption = {
		{GNAME, "useGui"},
		{GDESC, "Use Graphical User Interface. Possible Values: true / false. Default: false"},
		{GDFLT, false}
	};

	goptions.push_back(GOption(jsonGuiOption));

	return goptions;
}


int main(int argc, char* argv[])
{
	GOptions *gopts = new GOptions(argc, argv, defineOptions());

	// print settings wiwth defaults
	gopts->printSettings(true);


	// get option and print it from here
	int runno = gopts->getInt("runno");

	cout << " simpleExample runno: " << runno << endl;

	return EXIT_SUCCESS;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
