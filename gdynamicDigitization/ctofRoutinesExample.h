#ifndef CTOFROUTINEEXAMPLE
#define CTOFROUTINEEXAMPLE 1

// gdynamic
#include "gdynamicdigitization.h"

// c++
#include <string>
using namespace std;

class CTofRoutineExample : public GDynamicDigitization {

	// implementing 
public:
	bool loadConstants(int runno, string variation);
	bool checkPlugin();

private:

	double var1;
	int var2[2];
	vector<float> var3;
	string var4;

};

// tells the DLL how to create a GDynamicFactory
extern "C" GDynamicDigitization* GDynamicFactory(void) {
	return static_cast<GDynamicDigitization*>(new CTofRoutineExample);
}


#endif
