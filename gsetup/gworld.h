#ifndef  GWORLD_H
#define  GWORLD_H 1

// gsetup
#include "gworld.h"
#include "gsystem.h"
#include "gvolume.h"
#include "gmodifier.h"
#include "gworldOptions.h"

// glibrary
#include "gfactory.h"


class GWorld
{
public:
	// constructor from a jcard
	// by default all systems will have the same run number
	GWorld(GOptions* gopts);


private:
	map<string, GSystem*> gsystemsMap;     // key is system name
	map<string, GModifier*> gmodifiersMap; // key is volume name

	// manager to register the factories
	GManager gSystemManager;

	void registerFactoriesAndLoadSystems(GOptions* gopts);

public:
	// GWorld goptions
	vector<GOption> defineOptions();


	map<string, GSystem*> getSystemsMap() const {return gsystemsMap;}

	// key is sensitive name, value is path
//	map<string, string> getSensitiveVolumes();

};


#endif
