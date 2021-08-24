// gdynamic
#include "gdynamicdigitization.h"

// glibrary
#include "gtranslationTableConventions.h"
#include "gdataConventions.h"


// notice: if the energy deposited is very low (~50eV)
// the rounding error on the averave calculations could be up to 10^-3
GTrueInfoData* GDynamicDigitization::collectTrueInformation(GHit *ghit, int hitn)
{
	GTrueInfoData* trueInfoData = new GTrueInfoData(ghit);

	// notices:
	// we do each var hitbit group loop separately in case some are not filled

	// bit 0: always there
	ghit->calculateInfosForBit(0);
	G4ThreeVector avgGlobalPos = ghit->getAvgGlobaPosition();
	G4ThreeVector avgLocalPos  = ghit->getAvgLocalPosition();

	trueInfoData->includeVariable("totalEDeposited", ghit->getTotalEnergyDeposited());
	trueInfoData->includeVariable("avgTime", ghit->getAverageTime());
	trueInfoData->includeVariable("avgx",    avgGlobalPos.getX());
	trueInfoData->includeVariable("avgy",    avgGlobalPos.getY());
	trueInfoData->includeVariable("avgz",    avgGlobalPos.getZ());
	trueInfoData->includeVariable("avglx",   avgLocalPos.getX());
	trueInfoData->includeVariable("avgly",   avgLocalPos.getY());
	trueInfoData->includeVariable("avglz",   avgLocalPos.getZ());
	trueInfoData->includeVariable("hitn",  hitn);


	// bit 1
	return trueInfoData;
}

// this will set the ghit:
// - chargeAtElectronics
// - timeAtElectronics
// and will update ghit's gtouchable to include the GElectronic using the translation table (hardware address crate/slot/channel)
// this will exit with error if the TT is not defined, or if
void GDynamicDigitization::chargeAndTimeAtHardware(float time, int q, GHit *ghit, GDigitizedData *gdata)
{

	// gexit if translation table not defined
	if ( translationTable == nullptr ) {
		cerr << FATALERRORL << "Translation Table not found" << endl;
		gexit(EC__TTNOTFOUNDINTT);

	} else {

		// in order: crate, slot, channel
		vector<int> haddress = translationTable->getElectronics(ghit->getTTID()).getHAddress();

		// gexit if ghit haddress not initialized
		if ( haddress.front() == UNINITIALIZEDNUMBERQUANTITY) {
			cerr << FATALERRORL << "Translation Table found, but haddress was not initialized." << endl;
			gexit(EC__GIDENTITYNOTFOUNDINTT);
		} else {

			// everything is good.
			// include crate/slot/channel address
			// include payload time and charge for this hit

			gdata->includeVariable(CRATESTRINGID,   haddress[0]);
			gdata->includeVariable(SLOTSTRINGID,    haddress[1]);
			gdata->includeVariable(CHANNELSTRINGID, haddress[2]);
			gdata->includeVariable(TIMEATELECTRONICS, time);
			gdata->includeVariable(CHARGEATELECTRONICS, q);
		}
	}
}

