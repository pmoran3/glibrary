// gparticle
#include "gparticleOptions.h"
// namespace to define options
namespace gparticle {


	// System
	// ------

	void from_json(const json& j, JParticle& jpar) {
		j.at("pid").get_to(jpar.pid);
		j.at("multiplicity").get_to(jpar.multiplicity);
		j.at("px").get_to(jpar.px);
		j.at("py").get_to(jpar.py);
		j.at("pz").get_to(jpar.pz);
		j.at("punit").get_to(jpar.punit);
	}

	// method to return a vector of GDetectors from a structured option
	vector<JParticle> getJParticles(GOptions *gopts) {

		vector<JParticle> jparticles;

		auto jpars = gopts->getStructuredOptionAssignedValues("gparticle");

		// looking over each of the vector<json> items
		for ( const auto& jpar: jpars ) {
			jparticles.push_back(jpar.get<JParticle>());
		}

		return jparticles;
	}



	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;

		// gparticle
		// ---------

		// gparticle is cumulative structured (groupable): can use -add
		json jpid = {
			{GNAME, "pid"},
			{GDESC, "particle id. Follow the PDG Monte Carlo Particle Numbering Scheme."},
			{GDFLT, NODFLT}
		};
		json jmulti = {
			{GNAME, "multiplicity"},
			{GDESC, "How many copies of this particle will be generated per event"},
			{GDFLT, 1}
		};

		json jpx = {
			{GNAME, "px"},
			{GDESC, "x component of the momentum. Default: 0. "},
			{GDFLT, 0}
		};

		json jpy = {
			{GNAME, "py"},
			{GDESC, "y component of the momentum. Default: 0. "},
			{GDFLT, 0}
		};

		json jpz = {
			{GNAME, "pz"},
			{GDESC, "z component of the momentum. Default: 0. "},
			{GDFLT, 0}
		};

		json jpunit = {
			{GNAME, "punit"},
			{GDESC, "Unit for the particle momentum. Default: \"MeV\" "},
			{GDFLT, "MeV"}
		};

		json jparticleOption = {
			jpid,
			jmulti,
			jpx,
			jpy,
			jpz,
			jpunit
		};

		vector<string> help;
		help.push_back("");
		help.push_back("For example, a 5 GeV electron along z: +gparticle={pid: 11; pz: 5000;}");

		// the last argument refers to "cumulative"
		goptions.push_back(GOption("gparticle", "adds a particle to the event generator", jparticleOption, help, true));

		return goptions;
	}

}
