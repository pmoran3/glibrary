#ifndef  GOPTIONS_CONVENTIONS_H
#define  GOPTIONS_CONVENTIONS_H  1

// these are also defined in gstring
// in case a library does not need goption
#ifndef FATALERRORL
	#define	FATALERRORL " ☣︎"
	#define	GWARNING    " ⚠︎"
	#define	GOPTIONITEM " ・ "
#endif

//! formatting spaces for the help
#define HELPFILLSPACES  "                           "

//! characther to be displayed when summarizing options, includes indent
#define ITEMCHAR  " ◻︎"

//! verbosity levels
#define GVERBOSITY_SILENT  0
#define GVERBOSITY_SUMMARY 1
#define GVERBOSITY_DETAILS 2
#define GVERBOSITY_ALL     3

// verbosity description. name must match the above definitions + _D
#define GVERBOSITY_SILENT_D  " ・ 0: silent\n"
#define GVERBOSITY_SUMMARY_D " ・ 1: summary information\n"
#define GVERBOSITY_DETAILS_D " ・ 2: detailed information\n"
#define GVERBOSITY_ALL_D     " ・ 3: max verbosity\n"


#endif
