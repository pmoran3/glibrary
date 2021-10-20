#ifndef  GPARTICLE_H_OPTIONS
#define  GPARTICLE_H_OPTIONS 1

// glibrary
#include "goptions.h" 

namespace gparticle {

	// returns array of options definitions
	vector<GOption> defineOptions();


	// single particle is a structured option
	// ------

	struct JParticle {
		string pname;
		int pid;
		int multiplicity;

		float px;
		float py;
		float pz;
		string punit;

		float vx;
		float vy;
		float vz;
		string vunit;

	};

	void from_json(const json& j, JParticle& jpar);

	// method to return a vector of JSystem from a structured option
	vector<JParticle> getJParticles(GOptions *gopts);

}




#endif
