#ifndef  GSYSTEM_H
#define  GSYSTEM_H 1

// gsystem
#include "gvolume.h"

// c++
#include <map>
using std::map;

// a single GSystem is a collection of volumes that refers to a single detector system
// for example: a calorimeter; a drift chamber; a time-of-flight
class GSystem
{
	
public:
	// constructor, from command line or jcard
	GSystem(string n, string f, string v, int verbosity);

private:
	string      name;               // System name, with path to it. We save it here to use formVolumeKey
	string   factory;               // Factory that builds the detector
	string variation = "default";   // Variation of the detector. Default is "default"

	// map containing the volumes
	// the key is system + volume name;
	// the names must be unique in each system
	// each system name must be unique
	map<string, GVolume*> *gvolumesMap;

	string formVolumeKey(string detectorName) {
		return name + "_" + detectorName;
	}

public:
	string getName() const      { return name; }
	string getFactory() const   { return factory; }
	string getVariation() const { return variation; }

	
	// returns a vector of import files, checking all possible directories.
	// this should be in some general utility library? gutilities?
	// vector<string> gImportFiles(vector<string> locations, int verbosity, vector<string> possibleExtensions);

	// load all names in the directory matching extension
	// this should be in some general utility library? gutilities?
	// vector<string> loadImportFilesInDir(string path, DIR* directory, vector<string> withExtension);

	void addGVolume(vector<string> pars, int verbosity);
	// void addGImportedVolume(string importType, string filename, int verbosity);

	// need to filter system name from key
	GVolume* getGVolume(string detectorName) {

		string key = formVolumeKey(detectorName);

		if(gvolumesMap->find(key) != gvolumesMap->end()) {
			return (*gvolumesMap)[key];
		} else {
			return nullptr;
		}
	}
	
	map<string, GVolume*>* getGVolumesMap() const {return gvolumesMap;}

};



#endif
