// gdata 
#include "gEventDataCollection.h"


void GEventDataCollection::addDetectorTrueInfoData(string sdName, GTrueInfoData *data) {

	// digitized data not found, creating it
	if ( gdataCollection->find(sdName) == gdataCollection->end() ) {
		(*gdataCollection)[sdName] = new GDataCollection();
	}
	(*gdataCollection)[sdName]->addTrueInfoData(data);


}

void GEventDataCollection::addDetectorDigitizedData(string sdName, GDigitizedData *data) {

	// digitized data not found, creating it
	if ( gdataCollection->find(sdName) == gdataCollection->end() ) {
		(*gdataCollection)[sdName] = new GDataCollection();
	}
	(*gdataCollection)[sdName]->addDigitizedData(data);


}

