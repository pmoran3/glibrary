#ifndef  GSTREAMER_H
#define  GSTREAMER_H  1


class GStreamer
{

protected:

	string outputFileName;
	virtual bool openConnection() { return false;}
	virtual bool closeConnection() { return false;}


	// event virtual methods
	// one per event, called per geant4 run
	virtual bool startEvent() { return false;}
	virtual bool endEvent()   { return false;}

	virtual bool publishEvent(GEventData *eventData) { return false;}


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
