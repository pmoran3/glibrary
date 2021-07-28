// gdata 
#include "gEventData.h"

// glibrary

void GEventData::addDetectorDigitizedData(string sdName, GDigitizedData *dgtzData) {

	auto detectorHitCollection = gdataCollection.find(sdName);

	// not found, creating it
	if ( detectorHitCollection == gdataCollection.end() ) {
		gdataCollection[sdName] = new GDataCollection();
		gdataCollection[sdName]->addDigitizedData(dgtzData);
	}

	

}


vector<GTrueInfoData*>*  GEventData::getTrueInfoData(string detector) {
	if ( gdataCollection.find(detector) != gdataCollection.end()) {
		return gdataCollection[detector]->getTrueInfoData();
	} else {
		cout << FATALERRORL << "sensitive detector <" << detector << "> not found in GEventData map." << endl;
		gexit(EC__GSDETECTORNOTFOUND);
	}
	// never reached
	return nullptr;
}

vector<GDigitizedData*>* GEventData::getDigitizedData(string detector) {
	if ( gdataCollection.find(detector) != gdataCollection.end()) {
		return gdataCollection[detector]->getDigitizedData();
	} else {
		cout << FATALERRORL << "sensitive detector <" << detector << "> not found in GEventData map." << endl;
		gexit(EC__GSDETECTORNOTFOUND);
	}
	// never reached
	return nullptr;
}
