#ifndef  EVENTDISPENSER_H
#define  EVENTDISPENSER_H  1


// glibrary
#include "goptions.h"
#include "gdynamicdigitization.h"

// TODO: make actual use of changing the constants in gDDGlobal
class  EventDispenser
{
public:
	EventDispenser(GOptions* gopt, map<string, GDynamicDigitization*> *gDDGlobal);

private:
	// from GOptions
	int verbosity;
	int neventsToProcess;
	int userRunno;

	// internal use
	// map of runs with weights as coming from the file
	map<int, double> runWeights;

	// map with numnber of events for each run, based on weight map
	map<int, int> runEvents;

	vector<int> listOfRuns;

	// fill the number of events map
	void distributeEvents(int neventsToProcess);

	void printRunsDetails(int neventsToProcess);

	int currentRunIndex;

	map<string, GDynamicDigitization*> *gDigitizationGlobal;

	// show digitization constants and parameters
	void showDigitizationParameters(string system, vector<string> digiConstants, vector<string> digiPars);

	// increase run index
	void setNextRun() {currentRunIndex++;}

public:
	// public api
	map<int, int> getRunEvents() {return runEvents;}
	int getCurrentRun()          {return listOfRuns[currentRunIndex];}

	// return sums of number of events across all runs
	int getTotalNumberOfEvents();

	// this will:
	// initiate all available gdynamic plugins for each run
	// run beamOn for each run
	// log on screen infos if enough verbosity
	int processEvents();


};


#endif
