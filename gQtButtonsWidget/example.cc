// gQtButtonsWidget
#include "gQtButtonsWidget.h"

// c++
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QFileInfo qrcFileInfoExecutable(argv[0]);
	QString rccPath = qrcFileInfoExecutable.absolutePath() + "/" + "exampleResources.rcc";
	QResource::registerResource(rccPath);

	vector<string> bicons;

	bicons.push_back(":/images/firstButton");
	bicons.push_back(":/images/secondButton");

	GQTButtonsWidget window(128, 128, bicons);
	window.show();

	return app.exec();
}

