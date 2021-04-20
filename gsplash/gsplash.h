/// \mainpage
/// \section Overview
/// The splash framework will show a splash image
/// with optional messages over-imposed on top of it.
///
/// \section Main Main Features
/// - messages sent in gui mode will be overimposed on the splash image
/// - messages sent in batch mode will be printed on screen
/// - splash image can be specified as a single string or by the goptions
///
/// \section User Interface
/// User can create a splash using either of these constructors:
/// - GSplash(gopts, gui): will use goptions to locate the image
/// - GSplash(imagename): will use image name directly (typically a qt resource)
///
/// \section Example
/// An example of how to load a splash and sending messages to it
///  is included in example.cc: \include example.cc
///
/// \file gsplash.h
/// \author \n Maurizio Ungaro
/// \author mail: ungaro@jlab.org\n\n\n

#ifndef GSPLASH_H
#define GSPLASH_H 1

// mlibrary
#include "goptions.h"

// Qt
#include <QtWidgets>

// c++
#include <string>

/// \class GSplash
/// <b> GSplash </b>\n\n
/// A splash screen can be loaded with goptions or by the image name\n
/// If the qt application is not running, the screen will not be displayed \n
/// and messages sent to gplash are logged on screen instead of printed\n
/// on top of the screen.\n
/// \author \n Maurizio Ungaro
/// \author mail: ungaro@jlab.org\n\n\n
class GSplash
{
public:
	GSplash(GOptions* gopt, bool);

private:
	//! splash is a library that could be used in
	//! batch mode as well. The gui option controls this
	bool  gui;
	QSplashScreen *splash;

public:
	~GSplash();
	void message(string);

	//! exits and returns focus
	void finish(QWidget *window) {if(splash != nullptr) splash->finish(window);}

	// gsplash options
	static map<string, GOption> defineOptions();
};

#endif


