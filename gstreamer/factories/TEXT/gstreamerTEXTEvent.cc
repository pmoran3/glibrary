// gstreamer
#include "gstreamerTEXTFactory.h"

bool GstreamerTextFactory::startEvent()
{
	if(ofile == nullptr) return false;
	
	*ofile  << "Event {" << endl;
	
	return true;
}




bool GstreamerTextFactory::endEvent()
{
	if(ofile == nullptr) return false;
	
	*ofile  << "}" << endl;
	
	return true;
}
