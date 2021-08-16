// gstreamer
#include "gstreamerTEXTFactory.h"


bool GstreamerTextFactory::publishEventTrueInfoData(string detectorName, vector<GTrueInfoData*>* trueInfoData) {


	if(ofile == nullptr) return false;
	
	*ofile << GTAB << "Detector " <<  detectorName << " True Info Bank {" << endl;
	for ( auto trueInfoHit: *trueInfoData ) {
		*ofile << GTABTAB << "Hit {" << endl;

		for ( auto [variableName, value]: trueInfoHit->getVariablesMap() ) {
			*ofile << GTABTAB << variableName << ": " << value << endl;
		}
		*ofile << GTABTAB << "}" << endl;


	}
	*ofile << GTAB << "}" << endl;


	return false;
}
