// g4display
#include "g4displayOptions.h"
#include "g4displayConventions.h"

vector<string> AVAILABLEG4VIEWERS = {
	"OGLSQt",
	"OGLIQt",
	"OGL"} ;

// namespace to define options
namespace g4display {

	// JView getter
	void from_json(const json& j, JView& jview) {
		j.at("viewer").get_to(jview.viewer);
		j.at("dimension").get_to(jview.dimension);
		j.at("position").get_to(jview.position);
	}

	// method to return a JView from a structured option
	JView getJView(GOptions *gopts) {

		// getting json detector from option
		auto jview = gopts->getStructuredOptionAssignedValues("gview");

		// projecting it onto GDetector structure
		return jview.front().get<JView>();
	}

	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;


		// JView
		// ------

		string VIEWERCHOICES = "g4 viewer. possible choice are:";
		for (auto c: AVAILABLEG4VIEWERS) {
			VIEWERCHOICES += "- " + c + "\n";
		}

		// gview option, non groupable
		json jsonViewer = {
			{GNAME, "viewer"},
			{GDESC, VIEWERCHOICES},
			{GDFLT, GDEFAULTVIEWERDRIVER}
		};
		json jsonViewDimension = {
			{GNAME, "dimension"},
			{GDESC, "g4 viewer dimension"},
			{GDFLT, GDEFAULTVIEWERSIZE}
		};
		json jsonViewPosition = {
			{GNAME, "position"},
			{GDESC, "g4 viewer position"},
			{GDFLT, GDEFAULTVIEWERPOS}
		};
		json jsonViewOption = {
			jsonViewer,
			jsonViewDimension,
			jsonViewPosition
		};

		vector<string> help;
		help.push_back("Defines the geant4 viewer, its dimensions and its position");
		help.push_back("");
		help.push_back("Example: -g4view={viewer: OGL; dimension: 1100x800; position: +200+100;}");

		// the last argument refers to "cumulative"
		goptions.push_back(GOption("g4view", "geant4 viewer, dimension, and position", jsonViewOption, help, false));


		return goptions;
	}

}
