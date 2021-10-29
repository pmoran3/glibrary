// gsystem
#include "gmaterial.h"

// c++
#include <iostream>

// glibrary
#include "gutilities.h"

using namespace std;
using namespace gutilities;

GMaterial::GMaterial(string s, vector<string> pars) : system(s)
{
	if( pars.size() != GMATERIALNUMBEROFPARS) {
		cerr << FATALERRORL << "incorrect number of material parameters (" << pars.size() << ") for " << pars[0] ;
		cerr << " It should be " << GMATERIALNUMBEROFPARS << endl;
		gexit(EC__GWRONGNUMBEROFPARS);
	} else {
		// size is already checked in addVolume, the only interface to volume
		int i=0;
		
		name         = trimSpacesFromString(pars[i++]);
		description  = trimSpacesFromString(pars[i++]);
		density      = stod(trimSpacesFromString(pars[i++]));

		setComponentsFromString(trimSpacesFromString(pars[i++]));

		

	}
}


ostream &operator<<(ostream &stream, GMaterial gMat)
{

	stream  << endl;
	//	stream << "   - Name:            "    << gMat.name     << "  -  " <<  gMat.description << endl;
	//	stream << "   - Mother:          "    << gMat.mother      << endl;
	//	stream << "   - Type:            "    << gMat.type        << endl;
	//	stream << "   - Parameters:      "    << gMat.parameters  << endl;
	//	stream << "   - Material:        "    << gMat.material << endl;
	//	stream << "   - E.M. Field:      "    << gMat.emfield << endl;
	//	stream << "   - Positions:       "    << gMat.pos << endl;
	//	stream << "   - Rotation(s):     "    << gMat.rot << endl;
	//	stream << "   - Digitization:    "    << gMat.digitization << endl;
	//	stream << "   - GIdentity:       "    << gMat.gidentity << endl;

	return stream;
}


void GMaterial::setComponentsFromString(string composition) {

	vector<string> allComponents = getStringVectorFromString(composition);

	for( int e=0; e < allComponents.size()/2; e++ ) {
		components.push_back(allComponents[e*2]);
		amounts.push_back(stod(allComponents[e*2+1]));
	}

}

