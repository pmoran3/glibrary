// gstreamer 
#include "gstreamer.h"

GStreamer::GStreamer(GOptions *gopts) {
	
}

// pragma todo: pass someting like map<string, bitset> to each detector to decide which data to publish
map<string, bool> GStreamer::publishEvent(GOptions *gopts, vector<GEventData*> *runData) {

	map<string, bool> gstreamReport;


	// looping over events
	for(auto eventData: (*runData)) {







	}




	return gstreamReport;

}
