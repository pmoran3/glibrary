#ifndef  GSYSTEM_H
#define  GSYSTEM_H 1

// gsetup
#include "gvolume.h"

// c++
#include <map>
using std::map;

class GSystem
{
	
public:
	// constructor, from command line or jcard
	GSystem(string n, string f, string v, int verbosity);

private:
	string      name;               // System name, with path to it
	string   factory;               // Factory that builds the detector
	string variation = "default";   // Variation of the detector. Default is "default"

	// map containing the volumes
	// the key is system + volume name;
	// the names must be unique in each system
	// each system name must be unique
	map<string, GVolume*> gvolumesMap;

	string formVolumeKey(string detectorName) {
		return name + detectorName;
	}

public:
	string getName() const      { return name; }
	string getFactory() const   { return factory; }
	string getVariation() const { return variation; }

	
	// returns a vector of import files, checking all possible directories.
	// this should be in some general utility library? gstrings?
	// vector<string> gImportFiles(vector<string> locations, int verbosity, vector<string> possibleExtensions);

	// load all names in the directory matching extension
	// this should be in some general utility library? gstrings?
	// vector<string> loadImportFilesInDir(string path, DIR* directory, vector<string> withExtension);


	void addGVolume(vector<string> pars, int verbosity);
	// void addGImportedVolume(string importType, string filename, int verbosity);

	// need to filter system name from key
	GVolume* getGVolume(string detectorName) {

		string key = formVolumeKey(detectorName);

		if(gvolumesMap.find(key) != gvolumesMap.end()) {
			return gvolumesMap[key];
		} else {
			return nullptr;
		}
	}
	
	map<string, GVolume*> getGVolumesMap() const {return gvolumesMap;}

};



#endif
