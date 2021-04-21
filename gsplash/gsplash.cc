// splash
#include "gsplash.h"

// qt
#include <QApplication>

GSplash::GSplash(string imageName) :  splash(nullptr)
{

	string picLocation = ".";
	string picName     = splashInfo[0];

	// optional second argument
	if(splashInfo.size() == 2) {
		if(getenv(splashInfo[0].c_str()) != nullptr) {
			picLocation = (string) getenv(splashInfo[0].c_str());
		}
	}

	string filename = picLocation + "/" + picName;

	// pixmap is empty if filename doesn't exist.
	QPixmap pixmap(filename.c_str());

	splash = new QSplashScreen(pixmap);
	splash->show();

	qApp->processEvents();

}

void GSplash::message(string msg)
{
	if(splash != nullptr) {

		splash->showMessage(msg.c_str(),  Qt::AlignLeft,  Qt::white );
		qApp->processEvents();

	}

}

