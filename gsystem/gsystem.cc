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

	vector<string> gvpaths = getStringVectorFromStringWithDelimiter(filename, ".");

	// first, get fist item w/o path
	string gvolumeName = getFileFromPath(gvpaths.front());
	// adding the rest except the extension
	for ( size_t i=1; i<gvpaths.size() - 1; i++) {
		gvolumeName += gvpaths[i];
	}

	// order is defined in gvolume.cc
	pars.push_back(gvolumeName);                           // 01 name
	pars.push_back(ROOTWORLDGVOLUMENAME);                  // 02 mother: by default is ROOTWORLDGVOLUMENAME
	pars.push_back(importType);                            // 03 type
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 04 parameters
	pars.push_back("G4_AIR");                              // 05 material: default is air
	pars.push_back("0*cm, 0*cm, 0*cm");                    // 06 pos
	pars.push_back("0*deg, 0*deg, 0*deg");                 // 07 rot
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 08 emfield
	pars.push_back("1");                                   // 09 visible
	pars.push_back("1");                                   // 10 style
	pars.push_back("999999");                              // 11 color
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 12 digitization
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 13 gidentity
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 14 copyOf
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 15 replicaOf
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 16 solidsOpr
	pars.push_back(UNINITIALIZEDSTRINGQUANTITY);           // 17 mirrot
	pars.push_back("1");                                   // 18 exist
	pars.push_back(filename);                              // 19 description: contains full path

	addGVolume(pars, verbosity);
}

