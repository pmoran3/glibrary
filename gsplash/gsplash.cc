// c++
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// splash
#include "gsplash.h"

// qt
#include <QApplication>



GSplash::GSplash(string imageName) :  splash(nullptr)
{
	// no argument, imageName is defaulted at NOSPLASHIMAGESELECTED
	if ( imageName == NOSPLASHIMAGESELECTED ) {

		auto filename = getenv(GSPLASHENVIRONMENT); // char*

		if ( filename != nullptr) {
			// pixmap is empty if filename doesn't exist.
			QPixmap pixmap(filename);
			splash = new QSplashScreen(pixmap);

		} else {
			cerr << " Environment variable " << GSPLASHENVIRONMENT << " must point to an image file. Exiting." << endl;
			exit(1);
		}

		cout << " Need to add gstring and goptions but loading image from environment" << endl;

	} else {
		string resourceImage = ":/" + imageName;

		QPixmap pixmap(resourceImage.c_str());
		splash = new QSplashScreen(pixmap);
		cout << " Need to add gstring and goptions but loading image from resource" << endl;
	}

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

