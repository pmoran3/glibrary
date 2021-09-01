#ifndef GSTREAMERROOTFACTORY_H
#define GSTREAMERROOTFACTORY_H 1

// gstreamer
#include "gstreamer.h"
#include "gRootTree.h"

// c++
#include <map>
//using std::ofstream;

// ROOT
#include "TFile.h"

class GstreamerRootFactory : public GStreamer
{
public:
	GstreamerRootFactory() {}

private:
	// open and close the output media
	bool openConnection();
	bool closeConnection();

	// event streams
	// start and end each event
	bool startEvent(GEventDataCollection* eventData);
	bool endEvent(GEventDataCollection* eventData);

	// write the header
	bool publishEventHeader(GEventDataCollectionHeader *gheader);

	// vector index is hit number
	bool publishEventTrueInfoData( string detectorName, const vector<GTrueInfoData*>*  trueInfoData);
	bool publishEventDigitizedData(string detectorName, const vector<GDigitizedData*>* digitizedData);

	// frame streams
	bool startStream(GFrameDataCollection* frameRunData);
	bool endStream(GFrameDataCollection* frameRunData);
	bool publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader);
	bool publishPayload(const vector<GIntegralPayload*> *payload);


private:
	TFile *rootfile;
	map<string, GRootTree*> *gRootTrees;

};

#endif // GSTREAMERTXTFACTORY_H

