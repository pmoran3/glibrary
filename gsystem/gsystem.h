#ifndef  GSYSTEM_H
#define  GSYSTEM_H 1

// gsystem
#include "gvolume.h"
#include "gmaterial.h"

// c++
#include <map>
using std::map;

// a single GSystem is a collection of volumes that refers to a single detector system
// for example: a calorimeter; a drift chamber; a time-of-flight
class GSystem
{
	
public:
	// constructor, from command line or jcard
	GSystem(string givenname, string factory, string variation, int verbosity);

private:

	// MARK: class vars
	string name;                    // System name
	string path;                    // Absolute/relative path
	string factoryName;             // Name of actory that builds the detector
	string variation = "default";   // Variation of the detector. Default is "default"

	inline const string formVolumeKey(string detectorName) const {
		if (detectorName == ROOTWORLDGVOLUMENAME) {
			return ROOTWORLDGVOLUMENAME;
		}
		return name + "__" + detectorName;
	}

	// map containing the volumes
	// the key is system + volume name;
	// the names must be unique in each system
	// each system name must be unique
	map<string, GVolume*> *gvolumesMap;

	// materials are part of a system and cannot be shared among systems
	// (for that, the G4 Material database should be sufficient
	map<string, GMaterial*> *gmaterialsMap;

public:
	inline const string getName()        const { return name; }
	inline const string getFactoryName() const { return factoryName; }
	inline const string getVariation()   const { return variation; }
	inline const string getFilePath()    const { return path + "/" + name; }


	// MARK: GVOLUMES

	// add root rootVolumeDefinition
	void addROOTVolume(string rootVolumeDefinition);

	// add gvolume using parameters (TEXT or MYSQL factories)
	void addGVolume(vector<string> pars, int verbosity);

	// add gvolume from file (CAD or GDML factories)
	void addVolumeFromFile(string importType, string filename, int verbosity);

	// need to filter system name from key
	GVolume* getGVolume(string volumeName) const;
	
	inline const map<string, GVolume*>* getGVolumesMap() const {return gvolumesMap;}


	// MARK: GMATERIALS

	// add gmaterial using parameters (TEXT or MYSQL factories)
	void addGMaterial(vector<string> pars, int verbosity);

	const GMaterial* getMaterialForGVolume(string volumeName) const;

	inline const map<string, GMaterial*>* getGMaterialMap() const {return gmaterialsMap;}

	
};



#endif
