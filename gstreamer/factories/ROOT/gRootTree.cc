#include "gRootTree.h"

// clears the maps vectors
bool GRootTree::initTreeForTheEvent()
{
	for(auto v: stringVars) {
		v.second->clear();
	}
	for(auto v: intVars) {
		v.second->clear();
	}
	for(auto v: floatVars) {
		v.second->clear();
	}
	for(auto v: doubleVars) {
		v.second->clear();
	}
	return true;
}
