#ifndef  GOPTIONS_DOXY_H
#define  GOPTIONS_DOXY_H  1
/// \mainpage
/// \section Overview
/// The framework provides command line and parsing of user
/// defined options in JSON formats.\n\n
/// and the <b>command line</b> options look like:\n
/// <pre>	-beam={ vertex: 0, 0, -3, cm; mom: electron, 4*GeV, 20*deg, 180*deg; }  </pre>
/// The corresponding <b>JSON</b> syntax is:\n
/// <pre>
/// "beam": {
/// 	"vertex": "0, 0, -3, cm",
/// 	"value": "electron, 4*GeV, 20*deg, 180*deg"
/// }
/// </pre>\n
///
/// \section Main Main Features:
/// \n
/// * Goptions can be dynamically added to an executable by a framework or plugin
/// * Superposition of  command line / steering card (JSON file with .jcard extension)
/// * JSON, HTML output for documentation
/// * Can import a jcard within another one (imports should be declared at the top of the jcard)
/// * Mechanism to project options onto user defined structure/class
///
/// \n
///
/// \section Interface C++ User Interface:
/// \n
/// The users defines his/her own GOption map by calling the GOptions constructor:
/// <pre> GOptions(argc, argv, defineOptions(), <ignore>)</pre>
///
/// \param defineOptions() is a function returning a <bmap<string, GOption></b>
/// \param ignore (int, optional): set to 1 to ignore options not found.
///
/// Check the example below to see how to define a few GOptions.
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
/// \section Libraries JSON
///
/// The JSON parser used is https://github.com/nlohmann/json. It's included as a single hpp.\n
///
/// A json validator can be found here: https://codebeautify.org/jsonvalidator
///
#endif

