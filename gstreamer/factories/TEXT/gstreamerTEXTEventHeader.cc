// gstreamer
#include "gstreamerTEXTFactory.h"


bool GstreamerTextFactory::publishEventHeader(GEventHeader *gheader)
{
	if(ofile == nullptr) return false;
	
	*ofile  << GTAB << "Header Bank {" << endl;
	*ofile  << GTABTAB << " time: " << gheader->getTimeStamp() << endl;
//	*ofile  << GTABTAB << " g4-local event number: " << gheader->getG4Evn() << endl;
	*ofile  << GTABTAB << " thread id: " << gheader->getThreadID() << endl;
//	*ofile  << GTABTAB << " random status: " << gh->getG4Rnd() << endl;
	*ofile  << GTABTAB << "}" << endl;

	return true;
}
