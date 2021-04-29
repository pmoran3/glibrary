// gdata
#include "gEventData.h"

// c++
#include <iostream>
#include <thread>
using std::thread;

int main(int argc, char* argv[])
{

	thread thrds[8];

	// Define a Lambda Expression instantiating and deleting event data
	auto f = [](int evn) {

		GEventData *eventData = new GEventData(new GEventHeader(evn, evn));

		// each event has evn*10 hits
		for (int h=0; h<evn*10; h++ ) {

		}

		delete eventData;

	};

	// sending each event to a different thread
	for ( int evn=1; evn<=8; evn++ ) {

		thrds[evn] = thread(f, evn);

	}

	// Wait for threads to finish
	for ( int evn=0; evn<8; evn++ ) {
		thrds[evn].join();
	}

	return EXIT_SUCCESS;
}

