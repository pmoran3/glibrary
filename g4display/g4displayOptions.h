#ifndef  G4DISPLAY_H_OPTIONS
#define  G4DISPLAY_H_OPTIONS 1

// glibrary
#include "goptions.h" 


namespace g4display {


	// G4View
	// ------

	struct JView {
		string viewer;
		string dimension;
		string position;
	};

	JView getJView(GOptions *gopts);

	void from_json(const json& j, JView& jview);

	// method to return a vector of JSystem from a structured option
	vector<JView> getSystems(GOptions *gopts);


	// returns array of options definitions
	vector<GOption> defineOptions();

}

#endif
