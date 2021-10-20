// gparticle
#include "gparticleOptions.h"
#include "gparticleConventions.h"

// namespace to define options
namespace gparticle {


	// System
	// ------

	void from_json(const json& j, JParticle& jpar) {
		j.at("pid").get_to(jpar.pid);
		j.at("pname").get_to(jpar.pname);
		j.at("multiplicity").get_to(jpar.multiplicity);
		j.at("p").get_to(jpar.p);
		j.at("theta").get_to(jpar.theta);
		j.at("phi").get_to(jpar.phi);
		j.at("punit").get_to(jpar.punit);
		j.at("aunit").get_to(jpar.aunit);
		j.at("vx").get_to(jpar.vx);
		j.at("vy").get_to(jpar.vy);
		j.at("vz").get_to(jpar.vz);
		j.at("vunit").get_to(jpar.vunit);
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
		json jpname = {
			{GNAME, "pname"},
			{GDESC, "particle name, for example \"proton\". This is not used if pid is given."},
			{GDFLT, NODFLT}
		};

		json jpid = {
			{GNAME, "pid"},
			{GDESC, "particle id. Follow the PDG Monte Carlo Particle Numbering Scheme. Overwrites pname."},
			{GDFLT, GPARTICLENOTDEFINED}
		};

		json jmulti = {
			{GNAME, "multiplicity"},
			{GDESC, "How many copies of this particle will be generated per event."},
			{GDFLT, 1}
		};

		json jp = {
			{GNAME, "p"},
			{GDESC, "particle momentum."},
			{GDFLT, 0}
		};

		json jtheta = {
			{GNAME, "theta"},
			{GDESC, "Particle polar angle. Default: 0. "},
			{GDFLT, 0}
		};

		json jphi = {
			{GNAME, "phi"},
			{GDESC, "Particle azimuthal angle. Default: 0. "},
			{GDFLT, 0}
		};

		json jpunit = {
			{GNAME, "punit"},
			{GDESC, "Unit for the particle momentum. Default: \"MeV\" "},
			{GDFLT, "MeV"}
		};

		json jaunit = {
			{GNAME, "aunit"},
			{GDESC, "Unit for the particle angles. Default: \"deg\" "},
			{GDFLT, "deg"}
		};

		json jvx = {
			{GNAME, "vx"},
			{GDESC, "x component of the particle vertex. Default: 0. "},
			{GDFLT, 0}
		};

		json jvy = {
			{GNAME, "vy"},
			{GDESC, "v component of the particle vertex. Default: 0. "},
			{GDFLT, 0}
		};

		json jvz = {
			{GNAME, "vz"},
			{GDESC, "z component of the particle vertex. Default: 0. "},
			{GDFLT, 0}
		};

		json jvunit = {
			{GNAME, "vunit"},
			{GDESC, "Unit for the particle vertex. Default: \"mm\" "},
			{GDFLT, "cm"}
		};
		json jparticleOption = {
			jpname,
			jpid,
			jmulti,
			jp,
			jtheta,
			jphi,
			jpunit,
			jaunit,
			jvx,
			jvy,
			jvz,
			jvunit
		};

		vector<string> help;
		help.push_back("");
		help.push_back("For example, a 5 GeV electron along z: +gparticle={\"name\": \"e-\"; \"pz\": 5000;}");

		// the last argument refers to "cumulative"
		goptions.push_back(GOption("gparticle", "adds a particle to the event generator", jparticleOption, help, true));

		return goptions;
	}

}
