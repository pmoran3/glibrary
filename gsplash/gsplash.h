#ifndef GSPLASH_H
#define GSPLASH_H 1

// gsplash
#include "gsplash.h"

// gstring for the exit codes
#include "gstringConventions.h"

// c++
#include <string>
using std::string;

// Qt
#include <QtWidgets>

#define GSPLASHENVIRONMENT    "GSPLASH"
#define NOSPLASHIMAGESELECTED "NOSPLASHIMAGESELECTED"

// exit codes: 190s
#define EC__NOSPLASHENVFOUND               191

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


