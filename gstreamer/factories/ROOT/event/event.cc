// gstreamer
#include "gstreamerROOTFactory.h"

bool GstreamerRootFactory::startEvent(GEventDataCollection* eventData)
{
	if(rootfile == nullptr) return false;

	return true;
}




bool GstreamerRootFactory::endEvent(GEventDataCollection* eventData)
{
	if(rootfile == nullptr) return false;

	return true;
}
