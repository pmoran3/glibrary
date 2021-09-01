// gstreamer
#include "gstreamerTEXTFactory.h"

bool GstreamerTextFactory::startEvent(GEventDataCollection* eventData)
{
	if(ofile == nullptr) return false;

	auto eventNumber = eventData->getHeader()->getG4LocalEvn();
	*ofile  << "Event n. " << eventNumber << "{" << endl;
	
	return true;
}




bool GstreamerTextFactory::endEvent(GEventDataCollection* eventData)
{
	if(ofile == nullptr) return false;

	int eventNumber = eventData->getHeader()->getG4LocalEvn();

	*ofile  << "} end of event " << eventNumber << endl;
	
	return true;
}
