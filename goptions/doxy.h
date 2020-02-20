#ifndef  GOPTIONS_DOXY_H
#define  GOPTIONS_DOXY_H  1
/// \mainpage
/// \section Overview
/// The framework provides command line and parsing of user
/// defined options in JSON or YAML formats.\n\n
/// The command line options have the format:\n
/// <pre>	-key={ currency: "USD", value: 42.99 }  </pre>
/// The corresponding <b>JSON</b> syntax is:\n
/// <pre>
/// "key": {
/// 	"currency": "USD",
/// 	"value": 42.99
/// }
/// </pre>\n
/// The corresponding <b>YAML</b> syntax is:\n
/// <pre>
/// key:
/// 	currency: "USD"
/// 	value: 42.99
/// </pre>
///
/// \section Main Main Features:
/// \n
/// * Categories organization
/// * Command line, JSON, YAML input
/// * JSON, YAML, HTML output
/// * Options can be added from external libraries / executables.
///
/// \n
///
/// \section Interface C++ User Interface:
/// \n
/// The users defines his/her own GOption map: \n
/// <pre> map<string, GOption></pre>
/// by calling the GOptions constructor:
/// <pre> GOptions(argc, argv, defineOptions(), <ignore>)</pre>
///
/// \param defineOptions() is a function returning a map<string, GOption>
/// \param ignore (int, optional): set to 1 to ignore options not found.
///
/// Check the example below to see how to define a few GOptions
///
/// \section Libraries JSON and YAML parser
///
/// The JSON parser used is https://github.com/nlohmann/json (single hpp include)
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

