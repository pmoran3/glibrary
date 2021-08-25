// eventDispenser 
#include "eventDispenserConventions.h"
#include "eventDispenser.h"

// c++
#include <fstream>
#include <random>
using namespace std;

// glibrary
#include "textProgressBar.h"

// geant4
#include "G4UImanager.hh"


EventDispenser::EventDispenser(GOptions* gopt, map<string, GDynamicDigitization*> *gDDGlobal) : gDigitizationGlobal(gDDGlobal) {
	verbosity        = gopt->getInt("eventDistributionv");
	string filename  = gopt->getString("runWeightsFile");
	variation        = gopt->getString("digitizationVariation");
	//	userRunno        = gopt->getInt("userRunno");
	int userRunno        = 1;

	neventsToProcess = gopt->getInt("n");


	// nothing to do here
	if(neventsToProcess == 0) return;

	// no filename
	// run number from options
	// number of events from options
	if(filename == UNINITIALIZEDSTRINGQUANTITY && neventsToProcess > 0 ) {
		// only one run, defined in the option
		runEvents[userRunno] = neventsToProcess;
		return;
	} else {
		// filename specified, reading it
		ifstream in(filename.c_str());
		if(!in) {
			cerr << EVENTDISPENSERLOGMSGITEM << " Error: can't open run weights input file " << filename << ". Check your spelling. Exiting. " << endl;
			gexit(EC__EVENTDISTRIBUTIONFILENOTFOUND);
		} else {
			if(verbosity >= GVERBOSITY_SUMMARY) {
				cout << EVENTDISPENSERLOGMSGITEM << " Loading run weights from " << filename << endl;
			}
			// filling weight map
			while (!in.eof()) {
				int run;
				double weight;
				in >> run >> weight;
				listOfRuns.push_back(run);
				runWeights[run] = weight;
				runEvents[run] = 0;
			}
			// distribute events according to weights
			distributeEvents(neventsToProcess);
		}
		in.close();

		if(verbosity >= GVERBOSITY_SUMMARY) {
			printRunsDetails(neventsToProcess);
		}
	}

}


void EventDispenser::distributeEvents(int nevts)
{
	// now randomizing the run of each event
	TextProgressBar bar(50, string(EVENTDISPENSERLOGMSGITEM) + " Distributing events according to run weights ", 0, nevts);

	// generating random number
	// reference: http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	random_device randomDevice;
	mt19937 generator(randomDevice());
	uniform_real_distribution<> randomDistribution(0, 1);

	for(int i=0; i<nevts; i++) {
		double randomNumber = randomDistribution(generator);

		double ww = 0;
		for(const auto &weight : runWeights) {
			ww += weight.second;
			if(randomNumber <= ww) {
				runEvents[weight.first]++;
				break;
			}
		}
		bar.setProgress(i);
	}
}


void EventDispenser::printRunsDetails(int neventsToProcess)
{
	int ntot = 0;

	cout << EVENTDISPENSERLOGMSGITEM << " EventDispenser initialized with " << neventsToProcess << " events distributed among " << runWeights.size() << " runs:" << endl;

	if(verbosity >= GVERBOSITY_SUMMARY) {

		for(const auto &weight : runWeights) {
			cout << GTAB << EVENTDISPENSERLOGMSGITEM << " run: " << weight.first << "\t weight: " << runWeights[weight.first] ;
			cout << "\t  n. events: " << runEvents[weight.first] << endl;
			ntot += runEvents[weight.first];
		}
	}
}

// sums number of events across all runs
int EventDispenser::getTotalNumberOfEvents()
{
	int n = 0;

	for(auto rEvents : runEvents) {
		n += rEvents.second;
	}

	return n;
}


// this will:
// initiate all available gdynamic plugins for each run
// run beamOn for each run
// log on screen infos if enough verbosity
int EventDispenser::processEvents()
{
	G4UImanager *g4uim = G4UImanager::GetUIpointer();

	for(auto &run : runEvents) {

		int runNumber = run.first;
		int nevents   = run.second;

		if(verbosity >= GVERBOSITY_SUMMARY) {
			cout << EVENTDISPENSERLOGMSGITEM << " Starting Run Number ∙" << runNumber << "∙,  processing " << nevents << " events." << endl;
		}

		// loads the constants
		for(auto [digitizationName, digiRoutine]: (*gDigitizationGlobal)) {
			if(verbosity >= GVERBOSITY_DETAILS) {
				cout << EVENTDISPENSERLOGMSGITEM << " Calling " << digitizationName << "digitization loadConstants for run " << runNumber << endl;
			}
			digiRoutine->loadConstants(runNumber, variation);
			digiRoutine->loadTT(runNumber, variation);
		}

		// I think we may need this here
		//g4uim->ApplyCommand("/run/initialize");
		g4uim->ApplyCommand("/run/beamOn " + to_string(nevents));



		if(verbosity >= GVERBOSITY_SUMMARY) {
			cout << EVENTDISPENSERLOGMSGITEM << " Run Number ∙" << runNumber << "∙ done with " << nevents << " events." << endl << endl;
		}
	}

	cout << endl;

	return 1;
}


// show digitization constants and parameters
void EventDispenser::showDigitizationParameters(string system, vector<string> digiConstants, vector<string> digiPars)
{
	for(auto dc: digiConstants) {
		cout << "  " << EVENTDISPENSERLOGMSGITEM << " " << system << ": " << dc << endl;
	}
	for(auto dp: digiPars) {
		cout << "  " << EVENTDISPENSERLOGMSGITEM << " " << system << ": " << dp << endl;
	}
}





