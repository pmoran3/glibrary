#ifndef CTOFROUTINEEXAMPLE
#define CTOFROUTINEEXAMPLE 1

// gdynamic
#include "gdynamicdigitization.h"

// c++
#include <string>

class CTofRoutineExample : public GDynamicDigitization {

public:
	// mandatory readout specs definitions
	bool defineReadoutSpecs();

	bool loadConstants(int runno, string variation);

private:

	double var1;
	int var2[2];
	vector<float> var3;
	string var4;
};



#endif
