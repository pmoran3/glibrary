// gsetup
#include "gsystem.h"
#include "gsetupConventions.h"

// glibrary
#include "gstring.h"
#include "goptionsConventions.h"
//using namespace gstring;

// c++
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// init system based on name, factory, variation and run number
GSystem::GSystem(string n, string f, string v, int r, int dr, int verbosity) :
name(n),
factory(f),
variation(v),
runNumber(r) {
	if(verbosity >= GVERBOSITY_SUMMARY) {
		cout << GSETUPLOGHEADER << " loading system " << name << " with factory: " << factory;
		cout << ", variation: " << variation << ", run number: " << runNumber ;
		if(dr != r) cout << " (non default) ";
		cout << endl;
	}
}

// build and add a gvolume to the map from system parameters
void GSystem::addGVolume(vector<string> pars, int verbosity)
{
	if( pars.size() != GVOLUMENUMBEROFPARS) {
		cerr << FATALERRORL << " Fatal Error: Incorrect number of system parameters (" << pars.size() << ") for " << pars[0] ;
		cerr << " It should be " << GVOLUMENUMBEROFPARS << endl;
		gexit(EC__GVOLUMENUMBEROFPARS);
	} else {
		string nameKey = formVolumeKey(pars[0]);
		
		if(gvolumesMap.find(nameKey) == gvolumesMap.end()) {

			gvolumesMap[nameKey] = new GVolume(pars);
			if(verbosity == GVERBOSITY_SUMMARY) {
				cout << GSETUPLOGHEADER << " adding gVolume " << pars[0] << " to gvolumes map." << endl;
			} else if(verbosity == GVERBOSITY_DETAILS) {
				cout << GSETUPLOGHEADER << " adding gVolume" << *(gvolumesMap[nameKey]) << endl;
			}
		} else {
			cerr << FATALERRORL << " Fatal error: a volume with the name " << nameKey << " already exists. " << endl;
			gexit(EC__GVOLUMEALREADYPRESENT);
		}
	}
}

// build and add an imported volume to the map
//void GSystem::addGImportedVolume(string importType, string filename, int verbosity)
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


//vector<string> GSystem::getAllVolumeNames() const
//{
//	vector<string> names;
//	for(auto &s: systems) {
//		names.push_back(s.first);
//	}
//	return names;
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

//string GSystem::getSystemPath()
//{
//	return getPathFromFilename(name);
//}


// returns the file stream, checking all possible directories.
//ifstream* GSystem::gSystemFile(int which, vector<string> locations, int verbosity)
//{
//	string fname;
//	if(which == 0)       fname = name +  "__materials_" ;
//	else if (which == 1) fname = name +  "__geometry_" ;
//	else if (which == 2) fname = name +  "__mirrors_" ;
//	fname += variation + ".txt";
//
//	// default dir is "."
//	ifstream *IN = new ifstream(fname.c_str());
//
//	if(!IN->good()) {
//		for(auto locs : locations) {
//			if(locs != NOTAPPLICABLE) {
//				string newName = locs + "/" + fname;
//				IN->open(newName.c_str());
//				if(verbosity == GVERBOSITY_ALL) {
//					cout << GSETUPLOGHEADER << " Trying " << newName << endl;
//				}
//				if(IN->good()) {
//					if(verbosity > GVERBOSITY_SILENT) {
//						cout << GSETUPLOGHEADER << " Opening " << newName << endl;
//					}
//					// file found
//					return  IN;
//				}
//			}
//		}
//		// file not found
//		cout << GSETUPLOGHEADER << " File " << fname << " not found " << endl;
//
//	}
//	// file was found
//	return IN;
//}

