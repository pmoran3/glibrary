// g4display
#include "g4displayOptions.h"
#include "gcamera.h"
using namespace g4display;

// glibrary
#include "gutilities.h"
using namespace gutilities;

// c++
#include <string>
using namespace std;

G4DisplayCamera::G4DisplayCamera(GOptions* gopts, QWidget* parent) : QWidget(parent)
{
	// projecting option onto JView
	JCamera jcamera = getJCamera(gopts);

	g4uim = G4UImanager::GetUIpointer();
	double thetaValue = getG4Number(jcamera.theta);
	double phiValue   = getG4Number(jcamera.phi);


	// Camera Direction Group
	// ----------------------

	// THETA
	cameraTheta = new QSlider(Qt::Horizontal);
	cameraTheta->setRange(0, 180);
	cameraTheta->setSingleStep(1);
	cameraTheta->setValue(thetaValue);
	QLabel *cameraThetaLabel = new QLabel(tr("θ"));

	QHBoxLayout *cameraThetaLayout = new QHBoxLayout;
	cameraThetaLayout->addWidget(cameraThetaLabel);
	cameraThetaLayout->addWidget(cameraTheta);

	// PHI
	cameraPhi = new  QSlider(Qt::Horizontal);
	cameraPhi->setRange(0, 360);
	cameraPhi->setSingleStep(1);
	cameraPhi->setValue(phiValue);
	QLabel *cameraPhiLabel = new QLabel(tr("ɸ"));

	QHBoxLayout *cameraPhiLayout = new QHBoxLayout;
	cameraPhiLayout->addWidget(cameraPhiLabel);
	cameraPhiLayout->addWidget(cameraPhi);

	// Combine THETA and PHI
	QVBoxLayout *cameraDirectionLayout = new QVBoxLayout;
	cameraDirectionLayout->addLayout(cameraThetaLayout);
	cameraDirectionLayout->addSpacing(12);
	cameraDirectionLayout->addLayout(cameraPhiLayout);

	QGroupBox *anglesGroup = new QGroupBox(tr("Camera Direction"));
	anglesGroup->setLayout(cameraDirectionLayout);

	connect ( cameraTheta, SIGNAL( valueChanged(int) ), this, SLOT( changeCameraDirection() ) );
	connect ( cameraPhi,   SIGNAL( valueChanged(int) ), this, SLOT( changeCameraDirection() ) );

	// Camera and background colors
	// ----------------------------


	// all layouts together
	// --------------------
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(anglesGroup);
	setLayout(mainLayout);
}

void G4DisplayCamera::changeCameraDirection()
{
	string command = "/vis/viewer/set/lightsThetaPhi " + to_string(cameraTheta->value()) + " " + to_string(cameraPhi->value());
	g4uim->ApplyCommand(command);

}


