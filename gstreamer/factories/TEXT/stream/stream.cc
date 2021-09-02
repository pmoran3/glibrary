// gstreamer
#include "gstreamerTEXTFactory.h"

bool GstreamerTextFactory::startStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;

	*ofile  << "Frame {" << endl;

	return true;
}




bool GstreamerTextFactory::endStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;

	*ofile  << "}" << endl;

	return true;
}
