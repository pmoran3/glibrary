// gsplash
#include "gsplash.h"

// qt
#include <QApplication>

// example of main declaring GOptions
int main(int argc, char* argv[])
{
	new QApplication(argc, argv);

	// get image from env variable "GSPLASH"
	GSplash gsplash = GSplash("example");

	for(int i=0; i<200; i++) {
		gsplash.message(to_string(i));
	}
	
	QMainWindow window;
	window.show();

	gsplash.finish(&window);
	return qApp->exec();


	return 1;
}

