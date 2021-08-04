#ifndef  G4DISPLAYCAMERA_H
#define  G4DISPLAYCAMERA_H 1

// qt
#include <QtWidgets>

// glibrary
#include "goptions.h"

// geant4 headers
#include "G4UImanager.hh"

class G4DisplayCamera: public QWidget {

	// metaobject required for non-qt slots
	Q_OBJECT

public:
	G4DisplayCamera(GOptions* gopts, QWidget* parent = Q_NULLPTR);

private:
	QSlider *cameraTheta;
	QSlider *cameraPhi;

	// geant4 UIManager
	G4UImanager  *g4uim;

private slots:
	void changeCameraDirection();

};


#endif
