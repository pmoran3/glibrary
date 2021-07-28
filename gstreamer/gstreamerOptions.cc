// gstreamer
#include "gstreamerOptions.h"

// namespace to define options
namespace gstreamer {


	// projecting options onto JOutput
	void from_json(const json& j, JOutput& output) {
		j.at("format").get_to(output.format);
		j.at("name").get_to(output.name);
	}

	// method to return a vector of GDetectors from a structured option
	vector<JOutput> getSystems(GOptions *gopts) {

		vector<JOutput> outputs;

		auto gouts = gopts->getStructuredOptionAssignedValues("goutput");

		// looking over each of the vector<json> items
		for ( const auto& gout: gouts ) {
			outputs.push_back(gout.get<JOutput>());
		}

		return outputs;
	}




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
		json jsonOutputFormat = {
			{GNAME, "format"},
			{GDESC, "Output file format"},
			{GDFLT, "na"}
		};
		json jsonOutputName = {
			{GNAME, "name"},
			{GDESC, "Output file name"},
			{GDFLT, "na"}
		};

		json jsonOutput = {
			jsonOutputFormat,
			jsonOutputName
		};


		vector<string> help;
		help.push_back("Define a Output format and name");
		help.push_back("");
		help.push_back("Example: +output={format: text; name: output.txt; }");
		help.push_back("");
		help.push_back("Current available formats:");
		help.push_back("");
		help.push_back(" - text");

		// the last argument refers to "cumulative"
		goptions.push_back(GOption("goutput", "Output format and name", jsonOutput, help, true));

		return goptions;
	}


}
