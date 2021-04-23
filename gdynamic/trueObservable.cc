// gdynamic
#include "gdynamic.h"



GObservables* GDynamic::trueInfoHit(GHit *ghit)
{
	GObservables* gdata = new GObservables();
	
	gdata->addObservable(ghit->getTotalEnergyDeposited(),  // variable value
						 "totEDep",                        // variable name
						 "MeV",         // variable description
						 "double");                        // save to disk as type

	
	
	return gdata;
}
