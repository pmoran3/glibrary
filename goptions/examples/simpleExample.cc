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
	json runTag = {
		{GNAME, "runno"},
		{GDESC, "Run number"},
		{GDFLT, 0}
	};

	goptions.push_back(GOption("runno", "run option", runTag));

	// activate gui. Default = no (batch mode)
	json guiTag = {
		{GNAME, "useGui"},
		{GDESC, "Graphical User Interface. Possible Values: 0/1. Default: 0"},
		{GDFLT, 0}
	};

	goptions.push_back(GOption("useGui", "gui option", guiTag));

	return goptions;
}


int main(int argc, char* argv[])
{
	GOptions *gopts = new GOptions(argc, argv, defineOptions());

	// print settings w/o defaults
	gopts->printSettings(false);

	return EXIT_SUCCESS;
}

