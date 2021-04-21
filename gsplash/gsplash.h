#ifndef GSPLASH_H
#define GSPLASH_H 1

// glibrary
#include "goptions.h"

// Qt
#include <QtWidgets>

class GSplash
{
public:

	GSplash(string imageName) {
		if(splash != nullptr) {
			delete splash ;
		}
	}

private:
	QSplashScreen *splash;

public:

	~GSplash();

	void message(string message);

	// exits and returns focus to window
	void finish(QWidget *window) {
		if(splash != nullptr) {
			splash->finish(window);
		}
	}

};

#endif


