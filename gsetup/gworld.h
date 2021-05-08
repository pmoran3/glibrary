#ifndef  GWORLD_H
#define  GWORLD_H 1

// gsetup
#include "gworld.h"
#include "gsystem.h"
#include "gvolume.h"
#include "gmodifier.h"
#include "gworldOptions.h"

class GWorld
{
public:
	// constructor from a jcard / command lines
	// load systems and modifiers map
	// load factories
	// run factory load system for each item in gsystemsMap
	// apply modifiers
	GWorld(GOptions* gopts);


private:
	map<string, GSystem*> gsystemsMap;     // key is system name
	map<string, GModifier*> gmodifiersMap; // key is volume name

public:
	// GWorld goptions
	vector<GOption> defineOptions();


	map<string, GSystem*> getSystemsMap() const {return gsystemsMap;}

	// key is sensitive name, value is path
//	map<string, string> getSensitiveVolumes();

};


#endif
