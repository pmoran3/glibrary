#ifndef CTOFROUTINEEXAMPLE
#define CTOFROUTINEEXAMPLE 1

// gdynamic
#include "gdynamic.h"

// c++
#include <string>
using namespace std;

class CTofRoutineExample : public GDynamic {

public:
	bool loadConstants(int runno, string variation);
	bool checkPlugin();

private:

	double var1;
	int var2[2];
	vector<double> var3;
	string var4;

};

extern "C" GDynamic* GDynamicFactory(void) {
	return static_cast<GDynamic*>(new CTofRoutineExample);
}


#endif
