#ifndef GSTREAMERJSROFACTORY_H
#define GSTREAMERJSROFACTORY_H 1

// gstreamer
#include "gstreamer.h"

#include <fstream>
using std::ofstream;

class GstreamerJSROFactory : public GStreamer
{
public:
	GstreamerJSROFactory() {}

private:
	// open and close the output media
	bool openConnection();
	bool closeConnection();

	// frame streams
	bool startStream(const GFrameDataCollection* frameRunData);
	bool endStream(const GFrameDataCollection* frameRunData);
	bool publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader);
	bool publishPayload(const vector<GIntegralPayload*> *payload);


private:
	ofstream *ofile = nullptr;
};

#endif // GSTREAMERJSROFACTORY_H

