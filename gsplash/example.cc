// gsplash
#include "gsplash.h"

// qt
#include <QApplication>

// c++
using namespace std;

// example of main declaring GOptions
int main(int argc, char* argv[])
{
	new QApplication(argc, argv);

	// get image from env variable "GSPLASH"
	GSplash gsplash = GSplash("example");

	for(int i=0; i<1000; i++) {
		gsplash.message(to_string(i));
	}
	
	QMainWindow window;
	window.show();

	gsplash.finish(&window);
	return qApp->exec();


	return 1;
}

