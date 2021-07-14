// gsystem
#include "gvolume.h"

// c++
#include <iostream>

// glibrary
#include "gstring.h"

using namespace std;
using namespace gstring;

GVolume::GVolume(vector<string> pars, string importPath)
{
	if( pars.size() != GVOLUMENUMBEROFPARS) {
		cerr << FATALERRORL << "Incorrect number of system parameters (" << pars.size() << ") for " << pars[0] ;
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

		description  = trimSpacesFromString(pars[i++]);

		string pexists = trimSpacesFromString(pars[i++]);
		exist = (pexists == "1") ? true : false;

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




