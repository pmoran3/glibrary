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
	(*gvolumesMap)[nameKey] = new GVolume(rootVolumeDefinition);
}


// define and add a CAD imported volume to gvolumesMap
//void GSystem::importCadVolumeFromFile(string importType, string filename, int verbosity)
//{
//	string nameKey = getFilenameFromFilenameWithPath(filename);
//	vector<string> pars;
//
//	// order is defined in gvolume.cc
//	pars.push_back(nameKey);                               // 01 name
//	pars.push_back(GWORLDNAME);                             // 02 mother
//	pars.push_back(importType + " import of " + filename); // 03 description
//	pars.push_back(importType + "Imported");               // 04 type
//	pars.push_back(NOTAPPLICABLE);                                  // 05 parameters
//	pars.push_back("1");                                   // 06 visible
//	pars.push_back("1");                                   // 07 style
//	pars.push_back("999999");                              // 08 color
//	pars.push_back("G4_AIR");                              // 09 material: default is air
//	pars.push_back(NOTAPPLICABLE);                                  // 10 emfield
//	pars.push_back("0*cm 0*cm 0*cm");                      // 11 pos
//	pars.push_back("0*deg 0*deg 0*deg");                   // 12 rot
//	pars.push_back(NOTAPPLICABLE); // 13 sensitivity
//	pars.push_back(NOTAPPLICABLE); // 14 touchableID
//	pars.push_back(NOTAPPLICABLE); // 15 copyOf
//	pars.push_back(NOTAPPLICABLE); // 16 replicaOf
//	pars.push_back("1");  // 17 pCopyNo
//	pars.push_back(NOTAPPLICABLE); // 18 solidsOpr
//	pars.push_back(NOTAPPLICABLE); // 19 mirror
//
//	if(gvolumesMap.find(nameKey) == gvolumesMap.end()) {
//
//		gvolumesMap[nameKey] = new GVolume(pars, filename);
//		if(verbosity == GVERBOSITY_ALL) {
//			cout << GSETUPLOGHEADER << " adding gVolume" << *(systems[nameKey]) << " from file " << filename << endl;
//		}
//	} else {
//		cout << GSETUPLOGHEADER << " Warning: a volume with the name " << nameKey << " already exists. This entry will be ignored." << endl;
//	}
//}



// returns a vector of import files, checking all possible directories.
//vector<string> GSystem::gImportFiles(vector<string> locations, int verbosity, vector<string> possibleExtensions)
//{
//	DIR *possibleDir = opendir(name.c_str());
//
//	if(possibleDir != nullptr) {
//		return loadImportFilesInDir(name, possibleDir, possibleExtensions);
//	} else {
//
//	}
//
//	return {};
//}

// returns filenames in the directory matching extension. Defined in utilities.cc.
//vector<string> GSystem::loadImportFilesInDir(string path, DIR* directory, vector<string> withExtension)
//{
//	vector<string> filesWithExtension;
//
//	// directory exists here
//	struct dirent *thisDirStructure = readdir(directory);
//	while(thisDirStructure != nullptr) {
//		string filename = thisDirStructure->d_name;
//
//		// checking that the file has the correct 3 char extension (with ".", that's 5 chars minimum
//		if(filename.size() > 4) {
//			string thisFilenameRoot(filename.begin(), filename.end() - 4);
//			string fileExtension(filename.end()-3, filename.end());
//
//			// if the file has the wanted extension, add it to the list
//			if(find(begin(withExtension), end(withExtension), fileExtension) != end(withExtension)) {
//				filesWithExtension.push_back(path + "/" + thisFilenameRoot + "." + fileExtension);
//			}
//		}
//		thisDirStructure = readdir(directory);
//	}
//
//	return filesWithExtension;
//}

