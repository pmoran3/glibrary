// gsetup
#include "gvolume.h"

// c++
#include <iostream>

// glibrary
#include "gstring.h"

using std::cerr;
using std::endl;
using gstring::trimSpacesFromString;

GVolume::GVolume(vector<string> pars, string importPath)
{
	if( pars.size() != GVOLUMENUMBEROFPARS) {
		cerr << FATALERRORL << " Fatal Error: Incorrect number of system parameters (" << pars.size() << ") for " << pars[0] ;
		cerr << " It should be " << GVOLUMENUMBEROFPARS << endl;
		gexit(GVOLUMENUMBEROFPARS);
	} else {
		// size is already checked in addVolume, the only interface to volume
		int i=0;
		
		name         = trimSpacesFromString(pars[i++]);
		mother       = trimSpacesFromString(pars[i++]);
		description  = trimSpacesFromString(pars[i++]);

		type        = trimSpacesFromString(pars[i++]);
		parameters  = trimSpacesFromString(pars[i++]);
		
		string pvis = trimSpacesFromString(pars[i++]);
		visible     = (pvis == "1") ? true : false;
		style       = stoi(trimSpacesFromString(pars[i++]));
		color       = trimSpacesFromString(pars[i++]);
		
		material    = trimSpacesFromString(pars[i++]);
		emfield     = trimSpacesFromString(pars[i++]);
		
		pos         = trimSpacesFromString(pars[i++]);
		rot         = trimSpacesFromString(pars[i++]);
		
		sensitivity = trimSpacesFromString(pars[i++]);
		touchableID = trimSpacesFromString(pars[i++]);
		
		copyOf      = trimSpacesFromString(pars[i++]);
		replicaOf   = trimSpacesFromString(pars[i++]);
		pCopyNo     = stoi(trimSpacesFromString(pars[i++]));
		solidsOpr   = trimSpacesFromString(pars[i++]);
		
		mirror      = trimSpacesFromString(pars[i++]);
		
		// modifiers - accessed through options/jcard
		shift = GSETUPNOTAPPLICABLEENTRY;
		tilt  = GSETUPNOTAPPLICABLEENTRY;
		exist = true;
		
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
	stream << "   - Col, Vis, Style: "    << gVol.color   << ", " << visibility << ", "  << style << endl;
	stream << "   - Material:        "    << gVol.material << endl;
	stream << "   - E.M. Field:      "    << gVol.emfield << endl;
	stream << "   - Position (cm):   "    << gVol.pos << endl;
	stream << "   - Rotation:        "    << gVol.rot << endl;
	stream << "   - Sensitivity:     "    << gVol.sensitivity << endl;
	stream << "   - Touchable ID:    "    << gVol.touchableID << endl;
	
	return stream;
}




