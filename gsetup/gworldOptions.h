#ifndef  GWORLDOPTIONS_H
#define  GWORLDOPTIONS_H 1

// glibrary
#include "goptions.h"

namespace gsetup {

	struct JSystem {
		string system;
		string factory;
		string variation;
		int runno;
	};

	void from_json(const json& j, JSystem& det);

	// method to return a vector of GDetectors from a structured option
	vector<JSystem> getDetectors(GOptions *gopts);

	// returns array of options definitions
	vector<GOption> defineOptions();
}


#endif
