#ifndef  G4DISPLAYSLICE_H
#define  G4DISPLAYSLICE_H 1

// qt
#include <QtWidgets>

// glibrary
#include "goptions.h"

// geant4 headers
#include "G4UImanager.hh"

class G4DisplaySlice: public QWidget {

public:
	G4DisplaySlice(GOptions* gopt, QWidget* parent = Q_NULLPTR);

private:
	// geant4 UIManager
	G4UImanager  *g4uim;

};


#endif
