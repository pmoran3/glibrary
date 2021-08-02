#ifndef  GSTREAMER_H
#define  GSTREAMER_H  1

// glibrary
#include "event/gEventDataCollection.h"
#include "gfactory.h"
#include "goptions.h"

// c++
#include <string>


class GStreamer
{

public:
//	GStreamer(GOptions *gopts);
	virtual ~GStreamer() = default;

	virtual bool openConnection()  { return false;}  // in GActionInitialization constructor
	virtual bool closeConnection() { return false;}  // in GActionInitialization destructor

	// runs the protected virtual methods to write events from a run to file
	map<string, bool> publishRunData(GOptions *gopts, vector<GEventDataCollection*> *runData);


protected:

	string outputFileName;

	// event virtual methods
	// one per event, called per geant4 run
	virtual bool startEvent() { return false;}
	virtual bool endEvent()   { return false;}
	virtual bool publishEventHeader(GEventDataCollectionHeader *gheader) { return false;}
	// vector index is hit number
	virtual bool publishEventTrueInfoData(vector<GTrueInfoData*>* trueInfoData)    { return false;}
	virtual bool publishEventDigitizedData(vector<GDigitizedData*>* digitizedData) { return false;}


	// stream virtual methods
//	virtual bool startStream() { return false;}
//	virtual bool endStream()   { return false;}
//	virtual bool publishStream(GEventData *eventData) { return false;}


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
