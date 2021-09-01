// gstreamer
#include "gRootTree.h"
#include "gstreamerROOTFactory.h"

// return header tree from map. If not there, initialize it.
GRootTree* GstreamerRootFactory::getOrInstantiateHeaderTree(GEventDataCollection* eventData) {

	// tree not found, initializing it
	if(gRootTrees->find(HEADERTREENAME) == gRootTrees->end()) {
		(*gRootTrees)[HEADERTREENAME] = new GRootTree(eventData->getHeader());
	}

	// return initialized tree
	return (*gRootTrees)[HEADERTREENAME];

}

GRootTree* GstreamerRootFactory::getOrInstantiateTrueInfoDataTree(string detectorName, GEventDataCollection* eventData){
	string treeName = detectorName + TRUEINFONAMEPREFIX;

	// tree not found, initializing it
	if(gRootTrees->find(treeName) == gRootTrees->end() ) {

		const vector<GTrueInfoData*>* gTrueInfoHitVector = eventData->getTrueInfoDataForDetector(detectorName);
		if ( gTrueInfoHitVector != nullptr) {
			if ( gTrueInfoHitVector->size() ) {
				(*gRootTrees)[treeName] = new GRootTree(detectorName, gTrueInfoHitVector->front());
			}
		}
	}

	// if we still don't have it, there's an error
	if(gRootTrees->find(treeName) == gRootTrees->end() ) {
		cerr << FATALERRORL << "tree <" << treeName << "> not found. This should never happen" << endl;
		gexit(EC__GSTREAMERROOTTREENOTFOUND);
	}

	// return initialized tree
	return (*gRootTrees)[treeName];

}

GRootTree* GstreamerRootFactory::getOrInstantiateDigitizedDataTree(string detectorName, GEventDataCollection* eventData) {
	string treeName = detectorName + DIGITIZEDNAMEPREFIX;

	// tree not found, initializing it
	if(gRootTrees->find(treeName) == gRootTrees->end() ) {

		const vector<GDigitizedData*>* gDigitizedHitVector = eventData->getDigitizedDataForDetector(detectorName);
		if ( gDigitizedHitVector != nullptr) {
			if ( gDigitizedHitVector->size() ) {
				(*gRootTrees)[treeName] = new GRootTree(detectorName, gDigitizedHitVector->front());
			}
		}
	}

	// if we still don't have it, there's an error
	if(gRootTrees->find(treeName) == gRootTrees->end() ) {
		cerr << FATALERRORL << "tree <" << treeName << "> not found. This should never happen" << endl;
		gexit(EC__GSTREAMERROOTTREENOTFOUND);
	}

	// return initialized tree
	return (*gRootTrees)[treeName];

}


// tells the DLL how to create a GStreamerFactory
extern "C" GStreamer* GStreamerFactory(void) {
	return static_cast<GStreamer*>(new GstreamerRootFactory);
}
