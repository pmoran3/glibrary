// gstreamer
#include "gstreamerJLABSROFactory.h"

bool GstreamerJSROFactory::startStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;

	// fill dataFrameHeader here or in publishFrameHeader


	return true;
}




bool GstreamerJSROFactory::endStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;


	return true;
}
