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

	// add a "runno" option
	// not groupable
	// no help, just description
	json jsonRunOption = {
		{GNAME, "runno"},
		{GDESC, "Run number"},
		{GDFLT, 11}
	};

	goptions.push_back(GOption(jsonRunOption));

	// add a "nthreads" option
	// not groupable
	// no help, just description
	json jsonNThreadsOption = {
		{GNAME, "nthreads"},
		{GDESC, "Number of hreadst"},
		{GDFLT, 4}
	};

	goptions.push_back(GOption(jsonNThreadsOption));


	// add a switch
	goptions.push_back(GOption("gui", "Use Graphical User Interface"));

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
