// gsystem
#include "gvolume.h"

// c++
#include <iostream>

// glibrary
#include "gutilities.h"

using namespace std;
using namespace gutilities;

GVolume::GVolume(vector<string> pars, string importPath)
{
	if( pars.size() != GVOLUMENUMBEROFPARS) {
		cerr << FATALERRORL << "incorrect number of system parameters (" << pars.size() << ") for " << pars[0] ;
		cerr << " It should be " << GVOLUMENUMBEROFPARS << endl;
		gexit(GVOLUMENUMBEROFPARS);
	} else {
		// size is already checked in addVolume, the only interface to volume
		int i=0;
		
		name         = trimSpacesFromString(pars[i++]);
		mother       = trimSpacesFromString(pars[i++]);
		type         = trimSpacesFromString(pars[i++]);
		parameters   = trimSpacesFromString(pars[i++]);
		material     = trimSpacesFromString(pars[i++]);
		pos          = trimSpacesFromString(pars[i++]);
		rot          = trimSpacesFromString(pars[i++]);
		emfield      = trimSpacesFromString(pars[i++]);
		string pvis  = trimSpacesFromString(pars[i++]);
		visible      = (pvis == "1") ? true : false;
		style        = stoi(trimSpacesFromString(pars[i++]));
		color        = trimSpacesFromString(pars[i++]);
		digitization = trimSpacesFromString(pars[i++]);
		touchableID  = trimSpacesFromString(pars[i++]);
		copyOf       = trimSpacesFromString(pars[i++]);
		replicaOf    = trimSpacesFromString(pars[i++]);
		solidsOpr    = trimSpacesFromString(pars[i++]);
		mirror       = trimSpacesFromString(pars[i++]);
		string pexists = trimSpacesFromString(pars[i++]);
		exist = (pexists == "1") ? true : false;

		description  = trimSpacesFromString(pars[i++]);

		// modifiers - accessed through options/jcard
		shift = GSYSTEMNOTAPPLICABLEENTRY;
		tilt  = GSYSTEMNOTAPPLICABLEENTRY;

		// set file with path if it's a CAD/GDML import
		importFilename = importPath;
	}
}


ostream &operator<<(ostream &stream, GVolume gVol)
{
	string style = "unknown";
	if(gVol.style == 0) {
		style = "wireframe";
	} else if(gVol.style == 1){
		style = "solid";
	}
	string visibility = "yes";
	if(!gVol.visible) {
		visibility = "no";
	}
	
	stream  << endl;
	stream << "   - Name:            "    << gVol.name     << "  -  " <<  gVol.description << endl;
	stream << "   - Mother:          "    << gVol.mother      << endl;
	stream << "   - Type:            "    << gVol.type        << endl;
	stream << "   - Parameters:      "    << gVol.parameters  << endl;
	stream << "   - Material:        "    << gVol.material << endl;
	stream << "   - E.M. Field:      "    << gVol.emfield << endl;
	stream << "   - Positions:       "    << gVol.pos << endl;
	stream << "   - Rotation(s):     "    << gVol.rot << endl;
	stream << "   - Digitization:    "    << gVol.digitization << endl;
	stream << "   - Touchable ID:    "    << gVol.touchableID << endl;
	stream << "   - Col, Vis, Style: "    << gVol.color   << ", " << visibility << ", "  << style << endl;

	return stream;
}




GVolume::GVolume(string rootVolumeDefinition) {

	vector<string> rootDefinitions = getStringVectorFromString(rootVolumeDefinition);
	string volumeParameters = "";

	for (int i=1; i<rootDefinitions.size()-1; i++) {
		volumeParameters += " " + rootDefinitions[i];
	}

	name         = ROOTWORLDGVOLUMENAME;
	mother       = MOTHEROFUSALL;
	type         = rootDefinitions[0];
	parameters   = volumeParameters;
	material     = rootDefinitions.back();
	pos          = "0*cm 0*cm 0*cm";
	rot          = "0*deg 0*deg 0*deg";
	emfield      = GSYSTEMNOTAPPLICABLEENTRY;
	visible      = false;
	style        = 0; // wireframe
	color        = "ccffff";
	digitization = GSYSTEMNOTAPPLICABLEENTRY;
	touchableID  = GSYSTEMNOTAPPLICABLEENTRY;
	copyOf       = GSYSTEMNOTAPPLICABLEENTRY;
	replicaOf    = GSYSTEMNOTAPPLICABLEENTRY;
	solidsOpr    = GSYSTEMNOTAPPLICABLEENTRY;
	mirror       = GSYSTEMNOTAPPLICABLEENTRY;
	exist        = 1;

	description  = "root volume";


	// modifiers - accessed through options/jcard
	shift = GSYSTEMNOTAPPLICABLEENTRY;
	tilt  = GSYSTEMNOTAPPLICABLEENTRY;

	// set file with path if it's a CAD/GDML import
	importFilename = "none";

}
