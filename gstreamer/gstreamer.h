#ifndef  GSTREAMER_H
#define  GSTREAMER_H  1

// glibrary
#include "event/gEventDataCollection.h"
#include "frame/gFrameDataCollection.h"
#include "gfactory.h"
#include "goptions.h"

// c++
#include <string>

class GStreamer
{

public:
	virtual ~GStreamer() = default;

	virtual bool openConnection()  { return false;}  // in GActionInitialization constructor
	virtual bool closeConnection() { return false;}  // in GActionInitialization destructor

	// called in GRunAction::EndOfRunAction
	// runs the protected virtual methods below to write events from a run to file
	// the key is the routine name + sensitive detector name
	map<string, bool> publishEventRunData(GOptions *gopts, vector<GEventDataCollection*> runData);

	// called in GRunAction::EndOfRunAction
	// runs the protected virtual methods below to write frames from a run to file
	// the key is the routine name + frame streamer id
	map<string, bool> publishFrameRunData(GOptions *gopts, GFrameDataCollection* frameRunData);

	void setOutputName(string output) {outputFileName = output;}
	void setStreamType(string stype)  {streamType = stype;}
	inline string const getStreamType() const {return streamType;}

protected:

	string outputFileName = UNINITIALIZEDSTRINGQUANTITY;
	string streamType     = UNINITIALIZEDSTRINGQUANTITY;

	// event virtual methods called by publishRunData, in order
	// --------------------------------------------------------
	
	virtual bool startEvent(GEventDataCollection* eventData) { return false;}
	virtual bool publishEventHeader(GEventDataCollectionHeader *gheader) { return false;}
	// vector index is hit number
	virtual bool publishEventTrueInfoData(string detectorName,  const vector<GTrueInfoData*>* trueInfoData)   { return false;}
	virtual bool publishEventDigitizedData(string detectorName, const vector<GDigitizedData*>* digitizedData) { return false;}
	virtual bool endEvent(GEventDataCollection* eventData)   { return false;}

	// stream virtual methods
	virtual bool startStream(GFrameDataCollection* frameRunData) { return false;}
	virtual bool publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader) { return false;}
	virtual bool publishPayload(const vector<GIntegralPayload*> *payload)           { return false;}
	virtual bool endStream(GFrameDataCollection* frameRunData)   { return false;}


public:

	// method to dynamically load factories
	static GStreamer* instantiate(const dlhandle handle) {

		if(handle == nullptr) return nullptr;

		void *maker = dlsym(handle , "GStreamerFactory");

		if (maker == nullptr) return nullptr;

		typedef GStreamer* (*fptr)();

		// static_cast not allowed here
		// see http://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast
		// need to run the DLL GMediaFactory function that returns the factory
		fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

		return func();
	}


};


#endif
