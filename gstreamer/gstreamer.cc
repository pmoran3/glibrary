// gstreamer 
#include "gstreamer.h"


// pragma todo: pass someting like map<string, bitset> to each detector to decide which data to publish
// TODO: stream
map<string, bool> GStreamer::publishRunData(GOptions *gopts, vector<GEventDataCollection*> runData) {

	map<string, bool> gstreamReport;

	// TODO: this needs to run if it's requested by the gopts
	// option should be added to write this / or stream this
	// looping over events
	for(auto eventDataCollection: runData) {

		gstreamReport["Stream report #1 <startEvent>: "] = startEvent();
		gstreamReport["Stream report #2 <header>: "]     = publishEventHeader(eventDataCollection->getHeader());

		for (auto& [detectorName, gDataCollection] : *eventDataCollection->getDataCollection() ) {
			// publish true info
			string reportName = "Stream report #3 <" + detectorName + "__TrueInfo>: ";
			gstreamReport[reportName] = publishEventTrueInfoData(detectorName, gDataCollection->getTrueInfoData());

			// publish digitized data
			reportName = "Stream report #4: <" +  detectorName + "__Digitized>: ";
			gstreamReport[reportName] = publishEventDigitizedData(detectorName, gDataCollection->getDigitizedData());
		}
		gstreamReport["Stream report #5 <endEvent>: "] = endEvent();
	}

	return gstreamReport;
}
