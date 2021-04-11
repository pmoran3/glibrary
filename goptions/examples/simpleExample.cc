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
	json runTag = {
		{GNAME, "runno"},
		{GDESC, "Run number"},
		{GDFLT, 0}
	};

	goptions.push_back(GOption(runTag));

	// useGui option
	// not groupable
	// no help, just description
	json guiTag = {
		{GNAME, "useGui"},
		{GDESC, "Graphical User Interface. Possible Values: 0/1. Default: 0"},
		{GDFLT, 0}
	};

	goptions.push_back(GOption(guiTag));

	return goptions;
}


int main(int argc, char* argv[])
{
	GOptions *gopts = new GOptions(argc, argv, defineOptions());

	// print settings wiwth defaults
	gopts->printSettings(true);


	// get option and print it from here
	

	return EXIT_SUCCESS;
}

