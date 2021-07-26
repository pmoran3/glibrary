// gstreamer
#include "gstreamerOptions.h"

// namespace to define options
namespace gstreamer {

	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;


		json jsonGStreamerVerbosity = {
			{GNAME, "gstreamv"},
			{GDESC, GVERBOSITY_DESCRIPTION},
			{GDFLT, 1}
		};
		goptions.push_back(GOption(jsonGStreamerVerbosity));

		// default material to use when a material is not found
		json jsonOutputfile = {
			{GNAME, "output"},
			{GDESC, "Output filename and format(s)"},
			{GDFLT, "na"}
		};

		vector<string> help;

		help.push_back("A detector definition includes the geometry location, factory and variation");
		help.push_back("The geometry and variation are mandatory fields");
		help.push_back("The variation is optional, with \"default\" as default");

		goptions.push_back(GOption("output", "Output filename and format(s)", jsonOutputfile, help));


		return goptions;
	}


}
