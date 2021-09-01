#include "gRootTree.h"
#include "gstreamerConventions.h"

// clears the maps vectors
bool GRootTree::initTreeForTheEvent()
{
	for(auto v: stringVarsMap) {
		v.second->clear();
	}
	for(auto v: intVarsMap) {
		v.second->clear();
	}
	for(auto v: floatVarsMap) {
		v.second->clear();
	}
	for(auto v: doubleVarsMap) {
		v.second->clear();
	}
	return true;
}


// return header tree with initialized leafs
GRootTree::GRootTree(GEventDataCollectionHeader *gheader) {
	rootTree = new TTree(HEADERTREENAME, HEADERTREENAMESUFFIX);


}


GRootTree::GRootTree(string detectorName, GTrueInfoData* gdata) {
	string treeName = detectorName + TRUEINFONAMEPREFIX;
	string description = detectorName + " " + TRUEINFOTREENAMESUFFIX;

	rootTree = new TTree(treeName.c_str(), description.c_str());

}

GRootTree::GRootTree(string detectorName, GDigitizedData* gdata) {
	string treeName = detectorName + DIGITIZEDNAMEPREFIX;
	string description = detectorName + " " + DIGITIZEDTREENAMESUFFIX;

	rootTree = new TTree(treeName.c_str(), description.c_str());

}

// the second argument is needed to select the VarsMap type and its content
void GRootTree::registerVariable(string varname, int value) {
	if ( intVarsMap.find(varname) == intVarsMap.end() ) {
		intVarsMap[varname] = new vector<int>;
		rootTree->Branch(varname.c_str(), &intVarsMap[varname]);
	} else {
		std::cerr << FATALERRORL << "variable <" << varname << "> already exist in variable map of tree " << rootTree->GetName() << endl;
		gexit(EC__GSTREAMERVARIABLEEXISTS);
	}
}



void GRootTree::registerVariable(string varname, float value) {

}

void GRootTree::registerVariable(string varname, double value) {

}

void GRootTree::registerVariable(string varname, string value) {

}
