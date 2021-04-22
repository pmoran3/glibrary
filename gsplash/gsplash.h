#ifndef GSPLASH_H
#define GSPLASH_H 1

// doxygen
#include "gsplash.h"

// c++
#include <string>
using namespace std;

// Qt
#include <QtWidgets>

#define GSPLASHENVIRONMENT    "GSPLASH"
#define NOSPLASHIMAGESELECTED "NOSPLASHIMAGESELECTED"

class GSplash
{
private:
	QSplashScreen *splash;

public:

	GSplash(string imageName = NOSPLASHIMAGESELECTED);
	
	~GSplash() {
		if(splash != nullptr) {
			delete splash ;
		}
	}

	void message(string message);

	// called in program using GSplash
	// returns focus to program window
	void finish(QWidget *callingWindow) {
		if(splash != nullptr) {
			splash->finish(callingWindow);
		}
	}

};

#endif


