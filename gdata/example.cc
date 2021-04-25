// gdata
#include "gEventData.h"

// c++
#include <iostream>


int main(int argc, char* argv[])
{

	GEventData *eventData = new GEventData();


	for ( int i=0; i<10; i++) {
		eventData->setHeader(i, 10);
	}

	return 1;
}

