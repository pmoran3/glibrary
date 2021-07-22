#ifndef  GSYSTEM_CONVENTIONS_H
#define  GSYSTEM_CONVENTIONS_H  1

// number of database pars defining a gvolume
#define GVOLUMENUMBEROFPARS        19

// exit codes: 200s
#define EC__GVOLUMEALREADYPRESENT  201
#define EC__GVOLUMENUMBEROFPARS    202
#define EC__GSETUPFILENOTOFOUND    203
#define EC__GVOLUMENOTFOUND        204

#define GSYSTEMNOTAPPLICABLEENTRY  "na"
#define GSYSTEMLOGHEADER           " ❖ GSystem ▸ "
#define GWORLDNAME                 "world"
#define NOMODIFIER                 "noModifier"

#define GEMC_TEXTDB       "GEMC_TEXTDB"
#define GSYSTEMTXTFACTORY "GSystemTEXTFactory"
#define GSYSTEMCADFACTORY "GSystemCADFactory"
#define GSYSTEMGDMFACTORY "GSystemGDMLFactory"
#define GSYSTEMSQLFACTORY "GSystemMYSQLFactory"

#define ROOTWORLDGVOLUMENAME "root"
#define MOTHEROFUSALL        "akasha"

#endif
