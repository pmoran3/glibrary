// gstring
#include "gstring.h"
using namespace gstring;


// c++
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	
	if(argc != 2) {
		cerr << FATALERRORL << " Error: run example with exactly one argument" << endl;
	} else {
		
		string test = argv[1];
		vector<string> testResult = getStringVectorFromString(test);
		
		for(auto &s : testResult) {
			cout <<  SQUAREITEM << s << endl;
		}
	}
	
	return 1;
}

