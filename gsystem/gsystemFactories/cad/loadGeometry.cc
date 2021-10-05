// gsystem
#include "systemCadFactory.h"

// c++
#include <filesystem>
using namespace std;

void GSystemCADFactory::loadGeometry(GSystem *s, int verbosity)
{
	string dirLocation = searchForDirInLocations(s->getFilePath(), possibleLocationOfCadFiles);

	if ( filesystem::exists(dirLocation) ) {
		vector<string> cadFiles = getListOfFilesInDirectory(dirLocation, {".stl"});

		for(auto cf: cadFiles) {
			s->addVolumeFromFile(GSYSTEMCADTFACTORY, dirLocation + "/" + cf, verbosity);
		}
	} else {
		cerr << FATALERRORL << " CAD Directory >" << s->getFilePath() << "< not found." << endl;
		gexit(EC__GDIRNOTFOUND);
	}



}



