// g4system
#include "g4systemOptions.h"
#include "g4systemConventions.h"

// project goption to a system
namespace g4system {

	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;

		json jsonG4WorldVerbosity = {
			{GNAME, G4SYSTEMVERBOSITY},
			{GDESC, GVERBOSITY_DESCRIPTION},
			{GDFLT, 1}
		};
		goptions.push_back(GOption(jsonG4WorldVerbosity));

		// use this string option to print out informations about this volume at construction time
		json jsonVolumeLogVerbosity = {
			{GNAME, "logVolume"},
			{GDESC, "log all information for volume"},
			{GDFLT, "na"}
		};
		goptions.push_back(GOption(jsonVolumeLogVerbosity));

		// default material to use when a material is not found
		json jsonDefaultMaterial = {
			{GNAME, "defaultMaterial"},
			{GDESC, "default material to be used if the switch \"useDefaultMaterial\" is activated"},
			{GDFLT, "G4_Galactic"}
		};
		goptions.push_back(GOption(jsonDefaultMaterial));

		// add a "useDefaultMaterial" switch
		goptions.push_back(GOption("useDefaultMaterial", "use material defined by \"defaultMaterial\" option if a volume's material is not defined"));

		json jsonG4CheckOverlaps = {
			{GNAME, "checkOverlaps"},
			{GDESC, "check overlaps (need better help)"},
			{GDFLT, 0}
		};
		goptions.push_back(GOption(jsonG4CheckOverlaps));


		return goptions;
	}


}
