// splash
#include "gsplash.h"

// qt
#include <QApplication>

GSplash::GSplash(string imageName) :  splash(nullptr)
{
	if ( imageName == NOSPLASHIMAGESELECTED ) {

		string filename = (string) getenv(GSPLASHENVIRONMENT);

		// pixmap is empty if filename doesn't exist.
		QPixmap pixmap(filename.c_str());
		splash = new QSplashScreen(pixmap);


	}

//	// pixmap is empty if filename doesn't exist.
//	QPixmap pixmap(filename.c_str());
//
//	splash = new QSplashScreen(pixmap);

	if (splash != nullptr) {
		splash->show();
		qApp->processEvents();
	}
}

void GSplash::message(string msg)
{
	if(splash != nullptr) {
		splash->showMessage(msg.c_str(),  Qt::AlignLeft,  Qt::white );
		qApp->processEvents();
	}
}

