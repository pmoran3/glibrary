// g4display
#include "g4displayOptions.h"
#include "g4displayConventions.h"

vector<string> AVAILABLEG4VIEWERS = {
	"OGLSQt",
	"OGLIQt",
	"OGL"} ;

// namespace to define options
namespace g4display {

	// JView
	// -----
	void from_json(const json& j, JView& jview) {
		j.at("viewer").get_to(jview.viewer);
		j.at("dimension").get_to(jview.dimension);
		j.at("position").get_to(jview.position);
	}

	// method to return a JView from a structured option
	JView getJView(GOptions *gopts) {

		// getting json detector from option
		auto jview = gopts->getStructuredOptionAssignedValues("g4view");

		// projecting it onto GDetector structure
		return jview.front().get<JView>();
	}


	// JCamera
	// -----
	void from_json(const json& j, JCamera& jcamera) {
		j.at("theta").get_to(jcamera.theta);
		j.at("phi").get_to(jcamera.phi);
	}

	// method to return a JView from a structured option
	JCamera getJCamera(GOptions *gopts) {

		// getting json detector from option
		auto jcamera = gopts->getStructuredOptionAssignedValues("g4camera");

		// projecting it onto GDetector structure
		return jcamera.front().get<JCamera>();
	}

	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;


		// JView
		// -----

		string VIEWERCHOICES = "g4 viewer. possible choice are:\n";
		for (auto c: AVAILABLEG4VIEWERS) {
			VIEWERCHOICES += "\t\t\t\t- " + c + "\n";
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


		// JCamera
		// -------


		// gview option, non groupable
		json jsonCameraPhi = {
			{GNAME, "phi"},
			{GDESC, "geant4 camera phi"},
			{GDFLT, "0*deg"}
		};
		json jsonCameratheta = {
			{GNAME, "theta"},
			{GDESC, "geant4 camera theta"},
			{GDFLT, "0*deg"}
		};
		json jsonCameraOption = {
			jsonCameraPhi,
			jsonCameratheta
		};

		help.clear();
		help.push_back("Defines the geant4 camera");
		help.push_back("");
		help.push_back("Example: -g4camera={phi: 20*deg; theta: 15*deg;}");

		// the last argument refers to "cumulative"
		goptions.push_back(GOption("g4camera", "geant4 camera", jsonCameraOption, help, false));


		return goptions;
	}

}
