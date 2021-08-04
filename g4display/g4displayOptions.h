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

	void from_json(const json& j, JView& jview);

	// get JView from options
	JView getJView(GOptions *gopts);


	// G4Camera
	// --------

	struct JCamera {
		string phi;
		string theta;
	};

	void from_json(const json& j, JCamera& jcamera);

	// get JCamera from options
	JCamera getJCamera(GOptions *gopts);


	// returns the array of options definitions
	// ------------------------------------
	vector<GOption> defineOptions();


}

#endif
