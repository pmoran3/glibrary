// gstreamer
#include "gstreamerTEXTFactory.h"

bool GstreamerTextFactory::startStream()
{
	if(ofile == nullptr) return false;

	*ofile  << "Frame {" << endl;

	return true;
}




bool GstreamerTextFactory::endStream()
{
	if(ofile == nullptr) return false;

	*ofile  << "}" << endl;

	return true;
}
