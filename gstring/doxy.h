#ifndef  GSTRING_DOXY_H
#define  GSTRING_DOXY_H  1
/// \mainpage
/// \section Overview
/// gstring provides basic string utilities (in a namespace) and conventions for stream i/o:
///
/// \section Main gstring namespace:
/// \n
/// * string trimSpacesFromString(string);
/// *	vector<string> getStringVectorFromString(string);
///
/// \n
///
/// \section Conventions Conventions:
/// \n
/// * Macro to define colors, for example FRED("my sentence")
/// * Verbosity levels from 0 to 3
/// * FATALERRORL, GWARNING, POINTITEM, CIRCLEITEM, SQUAREITEM strings
///
///
/// \section example
/// An example of defineOptions() that creates two categories is in example.cc: \include example.cc
/// Running <i>example -h</i> will produce the following log:
/// ~~~~
///
/// Usage:
///
/// > -h, -help, --help: print this message and exit.
/// > -help-all:  print all available options and exit.
/// > -help-html:  print all available options in HTML format (options.html) and exit.
///
/// > Available categories
///   -help-general........:  general related options
///   -help-process........:  process related options
///   -help-time...........:  time related options
///
/// ~~~~

#endif
