#ifndef  GOPTIONS_CONVENTIONS_H
#define  GOPTIONS_CONVENTIONS_H  1


#define HELPFILLSPACE "                              "

//  TAGS
#define GNAME          "JsonTagGNAME"
#define GDESC          "JsonTagGDESCription"
#define GDFLT          "jsonTagDefault"
#define NODFLT          "NODFLT"

#define IMPORTJCARD "import jcard"

#define GDEBUGSTRING  "-gdebug"
#define GSTRICTSTRING "-gstrict"

#define LISTOPTIONARROW "\t → "
#define PRINTALLOPTIONS "printAllOptions"
#define GOPTIONDOCUMENTATION "https://gemc.github.io/glibrary/goptions/"

// standardizing verbosity
#define GVERBOSITY_SUMMARY 1 // prints only summary message
#define GVERBOSITY_DETAILS 2 // print all details
#define GVERBOSITY_DESCRIPTION "Possible values: 0: shush; 1: summary message; 2: log everything"   //

// exit codes: 100s
#define EC__NOOPTIONFOUND               101
#define EC__MANDATORYOPTIONNOTFOUND     102
#define EC__NOADDFORCUMULATIVE          103
#define EC__ADDFORNONCUMULATIVE         104
#define EC__JSONPARSEERROR              105
#define EC__OPTIONSHOULDNOTBESTRUCTURED 106
#define EC__NONCUMULATIVEALREADYPRESENT 107
#define EC__OPTIONNOTASSIGNED           108
#define EC__SWITCHALREADYPRESENT        109

// template to be filled by libraries utilizing goptions
namespace goptions {

}


#endif

