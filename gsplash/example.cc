/// \file example.cc

// example on how to use the splash framework library

// gsplash
#include "gsplash.h"


// distinguishing between graphical and batch mode
// in the example we alway use the graphic
QCoreApplication* createApplication(int &argc, char *argv[], bool gui)
{
	if(gui) {
		return new QApplication(argc, argv);
	} else {
		return new QCoreApplication(argc, argv);
	}
}

//! example of main declaring GOptions
int main(int argc, char* argv[])
{
	QApplication(argc, argv);

	// get image from env variable "GSPLASH"
	GSplash gsplash = GSplash();

	for(int i=0; i<200; i++) {
		gsplash.message(to_string(i));
	}
	
	QMainWindow window;
	window.show();

	gsplash.finish(&window);
	return qApp->exec();


	return 1;
}

