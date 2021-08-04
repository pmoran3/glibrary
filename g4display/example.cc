// g4display
#include "g4display.h"
#include "g4displayOptions.h"

// c++
#include <iostream>
using namespace std;

// qt
#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GOptions *gopts = new GOptions(argc, argv, g4display::defineOptions());
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

}

