#ifndef GROOTTREE_H
#define GROOTTREE_H 1

// c++
#include <map>

// ROOT
#include "TTree.h"

// glibrary
#include "event/gEventDataCollection.h"

#define TRUEINFONAMEPREFIX   "trueInfo_"
#define DIGITIZEDNAMEPREFIX  "digitized_"

#define EC__GSTREAMERROOTTREENOTFOUND   850

#define HEADERTREENAME "header"

#define HEADERTREENAMESUFFIX    "GEMC Root Event Header"
#define TRUEINFOTREENAMESUFFIX  "True Info Data Root Tree"
#define DIGITIZEDTREENAMESUFFIX "Digitized Data Root Tree"

// connection between gdata and root
class GRootTree
{
public:

	// types of TTree
	GRootTree(GEventDataCollectionHeader *gheader);
	GRootTree(string detectorName, GTrueInfoData* gdata);
	GRootTree(string detectorName, GDigitizedData* gdata);

	// filling trees
	bool fillTree(GEventDataCollectionHeader *gheader);
	bool fillTree(GTrueInfoData* gdata);
	bool fillTree(GDigitizedData* gdata);

	// clear variables map below
	bool initTreeForTheEvent();

private:
	TTree *rootTree = nullptr;

	// variable maps
	// index is hit number
	map<string, vector<int>* >    intVarsMap;
	map<string, vector<float>* >  floatVarsMap;
	map<string, vector<double>* > doubleVarsMap;
	map<string, vector<string>* > stringVarsMap;


	// the second argument is needed to select the VarsMap type and its content
	void registerVariable(string varname, int value);
	void registerVariable(string varname, float value);
	void registerVariable(string varname, double value);
	void registerVariable(string varname, string value);

};

#endif // GROOTTREE_H

