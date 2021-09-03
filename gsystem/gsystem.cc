// gsystem
#include "gsystem.h"
#include "gsystemConventions.h"

// glibrary
#include "gutilities.h"
#include "goptionsConventions.h"

// c++
#include <iostream>
using namespace std;

// init system based on name, factory, variation and run number
GSystem::GSystem(string n, string f, string v, int verbosity) :
factoryName(f),
variation(v) {

	path = gutilities::getDirFromPath(n);
	name = gutilities::getFileFromPath(n);

	gvolumesMap = new map<string, GVolume*>;

	if(verbosity >= GVERBOSITY_SUMMARY) {
		cout << GSYSTEMLOGHEADER << "Instantiating GSystem <" << KWHT << name  << RST << "> using path <" << KWHT << path << RST << ">" << endl;
	}
}

// build and add a gvolume to the map from system parameters
void GSystem::addGVolume(vector<string> pars, int verbosity) {
	if( pars.size() != GVOLUMENUMBEROFPARS) {
		cerr << FATALERRORL << "incorrect number of system parameters (" << pars.size() << ") for " << pars[0] ;
		cerr << " It should be " << GVOLUMENUMBEROFPARS << endl;
		gexit(EC__GVOLUMENUMBEROFPARS);
	} else {
		string nameKey = formVolumeKey(pars[0]);
		
		if(gvolumesMap->find(nameKey) == gvolumesMap->end()) {

			(*gvolumesMap)[nameKey] = new GVolume(name, pars);
			if(verbosity >= GVERBOSITY_SUMMARY) {
				cout << GSYSTEMLOGHEADER << "adding gVolume " << pars[0] << " to gvolumes map with name <" << nameKey << ">" << endl;
			} 
		} else {
			cerr << FATALERRORL << "a volume with the name <" << nameKey << "> already exists. " << endl;
			gexit(EC__GVOLUMEALREADYPRESENT);
		}
	}
}

void GSystem::addROOTVolume(string rootVolumeDefinition) {
	string nameKey = formVolumeKey(ROOTWORLDGVOLUMENAME);
	// special constructor for root volume
	(*gvolumesMap)[nameKey] = new GVolume(rootVolumeDefinition);
}

// add volume from file (CAD or GDML factories)
// includes factory and filename in the definitions
void GSystem::addVolumeFromFile(string importType, string filename, int verbosity) {
	vector<string> pars;

	string gvolumeName = getFileFromPath(filename);

	// order is defined in gvolume.cc
	pars.push_back(gvolumeName);                           // 01 name
	pars.push_back(GWORLDNAME);                            // 02 mother: by default is GWORLDNAME
	pars.push_back(importType + " import of " + filename); // 03 description: contains full path
	pars.push_back(importType);                            // 04 type
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 05 parameters
	pars.push_back("1");                                   // 06 visible
	pars.push_back("1");                                   // 07 style
	pars.push_back("999999");                              // 08 color
	pars.push_back("G4_AIR");                              // 09 material: default is air
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 10 emfield
	pars.push_back("0*cm 0*cm 0*cm");                      // 11 pos
	pars.push_back("0*deg 0*deg 0*deg");                   // 12 rot
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 13 sensitivity
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 14 touchableID
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 15 copyOf
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 16 replicaOf
	pars.push_back("1");                                   // 17 pCopyNo
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 18 solidsOpr
	pars.push_back(GSYSTEMNOTAPPLICABLEENTRY);             // 19 mirror

	addGVolume(pars, verbosity);
}

