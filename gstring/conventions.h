#ifndef  GSTRINGS_CONVENTIONS_H
#define  GSTRINGS_CONVENTIONS_H  1

// use of colors in iostream
// example:
// cout << BOLD(FBLU("I'm blue-bold.")) << endl;
// taken from:
// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RST  "\x1B[0m" // reset string

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#define FATALERRORL BOLD(FRED(" error: "))
#define GWARNING    BOLD(FYEL(" warning: "))
#define POINTITEM  " ・ "
#define CIRCLEITEM " ◦ "
#define SQUAREITEM " ◻︎ "


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
