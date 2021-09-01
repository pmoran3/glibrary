#ifndef GROOTTREE_H
#define GROOTTREE_H 1

// c++
#include <map>

// ROOT
#include "TTree.h"

// glibrary
#include "event/gEventDataCollection.h"


// connection between gdata and root
class GRootTree
{
public:
	// return header tree with initialzed leafs
	GRootTree(GEventDataCollectionHeader *gheader);

	// return observables tree with initialzed leafs
	GRootTree(string tName, GEventDataCollection* eventData);

	bool initTreeForTheEvent();

	// filling trees
	bool fillTree(GEventDataCollectionHeader *gheader);
	bool fillTree(GEventDataCollection* eventData);

//	bool defineNewVar(string varName, GObservableType gt);

private:
	TTree *rootTree;

	// variable maps
	map<string, vector<int>* >    intVars;
	map<string, vector<float>* >  floatVars;
	map<string, vector<double>* > doubleVars;
	map<string, vector<string>* > stringVars;

};

#endif // GROOTTREE_H

