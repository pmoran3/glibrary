/// \mainpage
/// \section Overview
/// The framework provides command line and parsing of user
/// defined options in JSON formats.\n\n
/// The command line options have the format:\n
/// <pre>	-beam={ vertex: 0, 0, -3, cm; mom: electron, 4, 20, 180; }  </pre>
/// The corresponding <b>JSON</b> syntax is:\n
/// <pre>
/// "beam": {
/// 	"vertex": "0, 0, -3, cm",
/// 	"value": electron, 4, 20, 180
/// }
/// </pre>\n
///
/// \section Main Main Features:
/// \n
/// * Categories organization
/// * Command line, JSON file (.jcard extension)
/// * JSON, HTML output
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


/**
 * @details Constructor
 * \param name option title
 * \param description summary description. This is used in the search.
 * \param joptionDefinition contains the verbosity (defaulted at silent) and array of these objects.
 * \param groupable if an option belongs to a group, options can be collected by using -add-<name>
 * \param help here we can put the full description of the option.
 * Example: { "tag": "tagname", "description": "tag description", "default": default value}
 */



/// Check the example below to see how to define a few GOptions
///
/// \section Libraries JSON parser
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

