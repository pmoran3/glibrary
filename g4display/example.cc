// g4display
#include "g4display.h"

// c++
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GOptions *gopts = new GOptions(argc, argv, G4Display::defineOptions(), 1);
	G4Display *g4Display = new G4Display(gopts);

	// main window
	QMainWindow *window = new QMainWindow();
	window->setWindowTitle(QString::fromUtf8("displayUI example"));
	window->resize(600, 800);

	// 
//	DisplayUI *dUI = new DisplayUI(gopts, window);
//	window->setCentralWidget(dUI);


	window->show();
//	delete dUI;
	delete g4Display;

	return app.exec();


	return 1;
}

