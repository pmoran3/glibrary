// g4display 
#include "g4display.h"
#include "g4displayOptions.h"
using namespace g4display;

// c++
using namespace std;

// geant4
#include "G4UImanager.hh"


G4Display::G4Display(GOptions* gopts)
{
	// PRAGMA TODO: add resolution option, hits options, here?
	// PRAGMA TOOO: if run/beamOn is given (e.g. command line options) then the label needs to be updated!

	// projecting option onto JView
	JView jview = getJView(gopts);

	string gemcViewAndOption = "/vis/open " + jview.viewer + " " + jview.dimension + " " + jview.position;

	G4UImanager* UIM = G4UImanager::GetUIpointer();

	if(UIM) {
		UIM->ApplyCommand("/vis/scene/create gemcLab");

		UIM->ApplyCommand(gemcViewAndOption);

		UIM->ApplyCommand("/vis/scene/add/axes 0 0 0 10 cm");

	} else {
		cout << " No UIManager found. " << endl;
	}

}
