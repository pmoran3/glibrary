#ifndef  GSYSTEM_H
#define  GSYSTEM_H 1


// gvolume
#include "gvolume.h"

// glibrary
//#include "goptions.h"
//#include "gfactory.h"

#define setupLogHeader " ⎚ gvolume ▸"
#define GWORLDNAME     "world"

// c++
#include <map>
#include "dirent.h" // for directory access to DIR object
using std::ifstream;
using std::map;

class GSystem
{
	
public:
	GSystem(string n, string f, string v, int r, int dr, int verbosity);

private:
	string      name;     // System name, with path to it
	string   factory;     // Factory that builds the detector
	string variation;     // Variation of the detector. Default is "default"
	int    runNumber;     // Run Number selected for this detector. Default is 1

	// map containing the volumes
	// the key is system + volume name so the names must be unique in each system
	// PRAGMA TODO:  this should be pointer ?
	map<string, GVolume*> systems;

	// system parameters:
	// - timewindow
	// - energy threshold
	map<string, double> systemParameters;

	// load all names in the directory matching extension. Defined in utilities.cc.
	vector<string> loadImportFilesInDir(string path, DIR* directory, vector<string> withExtension);


public:
	string getFactory() const { return factory; }
	string getName() const    { return name; }
	
	// returns the file stream, checking all possible directories. Defined in utilities.cc
	ifstream* gSystemFile(int which, vector<string> locations, int verbosity);  // 0: material. 1: geometry
	
	// returns a vector of import files, checking all possible directories. Defined in utilities.cc
	vector<string> gImportFiles(vector<string> locations, int verbosity, vector<string> possibleExtensions);
	
	void addGVolume(vector<string> pars, int verbosity);
	void addGImportedVolume(string importType, string filename, int verbosity);

	GVolume* getGVolume(string key) {
		if(systems.find(key) != systems.end()) {
			return systems[key];
		} else {
			return nullptr;
		}
	}
	
	map<string, GVolume*> getSytems() const {return systems;}
	vector<string> getAllVolumeNames() const;
	string getSystemPath();
	
};



#endif
