#ifndef GSTREAMERTXTFACTORY_H
#define GSTREAMERTXTFACTORY_H 1

// gstreamer
#include "gstreamer.h"

#include <fstream>
using std::ofstream;

class GstreamerTextFactory : public GStreamer
{
public:
	GstreamerTextFactory() {}

private:
	// open and close the output media
	bool openConnection();
	bool closeConnection();

	// start and end each event
	bool startEvent();
	bool endEvent();

	// write the header
	bool publishEventHeader(GEventDataCollectionHeader *gheader);

	// vector index is hit number
	bool publishEventTrueInfoData(vector<GTrueInfoData*>* trueInfoData);
	bool publishEventDigitizedData(vector<GDigitizedData*>* digitizedData);


private:
	// utility function to write observable
	// PRAGMA TODO: check if this is feasible for all output plugins. In case, make it virtual
	void writeObservables(map<string, int> observableAtIndex, int index);

private:
	ofstream *ofile = nullptr;
};

#endif // GSTREAMERTXTFACTORY_H

