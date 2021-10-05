// gsystem
#include "systemCadFactory.h"

void GSystemCADFactory::loadGeometry(GSystem *s, int verbosity)
{
	string dirLocation = searchForDirInLocations(s->getFilePath(), possibleLocationOfCadFiles);
	vector<string> cadFiles = getListOfFilesInDirectory(dirLocation, {".stl"});

	for(auto cf: cadFiles) {
		s->addVolumeFromFile(GSYSTEMCADTFACTORY, dirLocation + "/" + cf, verbosity);
	}
}



