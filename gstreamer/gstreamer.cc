// gstreamer 
#include "gstreamer.h"


// pragma todo: pass someting like map<string, bitset> to each detector to decide which data to publish
// TODO: stream
map<string, bool> GStreamer::publishRunData(GOptions *gopts, vector<GEventDataCollection*> runData) {

	map<string, bool> gstreamReport;

	// TODO: this needs to run if it's requested by the gopts
	// option should be added to write this / or stream this
	// looping over events
	for(auto eventData: runData) {

		gstreamReport["startEvent"] = startEvent();
		gstreamReport["header"]     = publishEventHeader(eventData->getHeader());

		for (auto& [detectorName, gDataCollection] : *eventData->getDataCollection() ) {
			// publish true info
			string dnameKey = detectorName + "__TrueInfo";
			gstreamReport[dnameKey] = publishEventTrueInfoData(detectorName, gDataCollection->getTrueInfoData());

			// publish digitized data
			dnameKey = detectorName + "__Digitized";
			gstreamReport[dnameKey] = publishEventDigitizedData(detectorName, gDataCollection->getDigitizedData());
		}


		gstreamReport["endEvent"] = endEvent();
	}



	return gstreamReport;
}
